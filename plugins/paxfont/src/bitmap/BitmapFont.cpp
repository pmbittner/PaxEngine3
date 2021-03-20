//
// Created by Paul Bittner on 14.03.2021.
//

#include <paxcore/service/Services.h>
#include <paxcore/rendering/factory/MeshFactory.h>
#include "paxfont/bitmap/BitmapFont.h"

namespace PAX::Font {
    BitmapFont::BitmapFont(
            const FontMetadata & metadata,
            const std::shared_ptr<Texture> &bitmap,
            const std::vector<CharacterInfo> &charInfo) :
            metadata(metadata), bitmap(bitmap)
    {
        for (const CharacterInfo & c : charInfo) {
            characters[c.key] = c;
        }
    }

    glm::vec2 BitmapFont::toUV(const glm::vec2 &pixelCoordinates) {
        glm::vec2 bitmapSize = bitmap->getSize();
        glm::vec2 pixelCoordsAsFloats = pixelCoordinates;
        glm::vec2 ret = pixelCoordsAsFloats / bitmapSize;
        return ret;
    }

    std::shared_ptr<Mesh> BitmapFont::bakeText(const TextBlock &text, glm::vec2 & outMeshSize) {
        auto * meshFactory = Services::GetFactoryService().get<MeshFactory>();
        if (!meshFactory) {
            PAX_THROW_RUNTIME_ERROR("There is no MeshFactory registered at the Services!");
        }

        std::vector<glm::vec2> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<glm::ivec3> faces;

        const auto invFontSize = 1.f / float(metadata.size);
        const glm::vec2 halfPixelOffsetUL(+0.5f, +0.5f);
        const glm::vec2 halfPixelOffsetUR(-0.5f, +0.5f);
        const glm::vec2 halfPixelOffsetLL(+0.5f, -0.5f);
        const glm::vec2 halfPixelOffsetLR(-0.5f, -0.5f);
        glm::ivec2 cursor{0, 0};
        glm::vec2 dimensions(0);
        float currentLineWidth = 0;
        for (const TextLine & line : text.lines) {
            for (const Character & letter : line.chars) {
                const auto & cIt = characters.find(letter);
                if (cIt != characters.end()) {
                    const CharacterInfo & cinfo = cIt->second;

                    glm::vec2 lowerLeft  = cursor - cinfo.textLineOffset;
                    glm::vec2 lowerRight = lowerLeft + glm::vec2(cinfo.width, 0);
                    glm::vec2 upperLeft  = lowerLeft - glm::vec2(0, cinfo.size.y);
                    glm::vec2 upperRight = upperLeft + glm::vec2(cinfo.width, 0);

                    const glm::vec2 fpos = cinfo.pos;
                    const glm::vec2 fsize = cinfo.size;
                    const int ll = vertices.size();
                    vertices.push_back(lowerLeft);
                    uvs.push_back(toUV(fpos + halfPixelOffsetLL));
                    const int lr = vertices.size();
                    vertices.push_back(lowerRight);
                    uvs.push_back(toUV(fpos + glm::vec2(fsize.x, 0) + halfPixelOffsetLR));
                    const int ul = vertices.size();
                    vertices.push_back(upperLeft);
                    uvs.push_back(toUV(fpos + glm::vec2(0, fsize.y) + halfPixelOffsetUL));
                    const int ur = vertices.size();
                    vertices.push_back(upperRight);
                    uvs.push_back(toUV(fpos + fsize + halfPixelOffsetUR));

                    faces.emplace_back(ur, ul, ll);
                    faces.emplace_back(ur, ll, lr);

                    // Maybe better not add cinfo.textLineOffset.x here.
                    float step = float(cinfo.width) + cinfo.textLineOffset.x;
                    cursor.x += step;
                    currentLineWidth += step;
                } else {
                    PAX_LOG(Log::Level::Warn, "Unsupported character \'" << letter << "\'!");
                }
            }
            cursor.x = 0;
            cursor.y -= metadata.height;

            if (currentLineWidth > dimensions.x) {
                dimensions.x = currentLineWidth;
            }
            currentLineWidth = 0;
        }
        dimensions.y = cursor.y;

        const glm::vec2 centerOffset = 0.5f *  dimensions;
        const glm::vec2 size = glm::vec2(dimensions.x, -dimensions.y);
        // normalize all vertices into a quad
        for (glm::vec2 & p : vertices) {
            p = (p - centerOffset) / size;
        }
        outMeshSize = invFontSize * size;

        std::shared_ptr<Mesh> mesh = meshFactory->create(vertices, faces);
        mesh->addAttribute(Mesh::UVs, uvs);
        mesh->upload();
        return mesh;
    }

    const std::shared_ptr<Texture> & BitmapFont::getBitmap() const {
        return bitmap;
    }

    TextLine TextLine::fromString(const std::string & s) {
        TextLine l;
        for (char i : s) {
            l.chars.emplace_back(std::string(1, i));
        }
        return l;
    }
}