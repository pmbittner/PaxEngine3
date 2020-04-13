//
// Created by Paul Bittner on 21.03.2020.
//

#include <paxcore/rendering/graphics/SpriteGraphics.h>
#include <paxcore/gameentity/property/Size.h>
#include <paxutil/reflection/EngineFieldFlags.h>
#include <meshfold/PortalGenerator.h>
#include <paxcore/rendering/data/ColourPalette.h>
#include "meshfold/Meshfold.h"

namespace PAX {
    static Mesh* getFirstMeshYouCanFindIn(const std::shared_ptr<Asset> & asset) {
        const auto & meshes = asset->getMeshes();
        if (meshes.empty()) {
            for (const std::shared_ptr<Asset> & child : asset->getChildren()) {
                Mesh * m = getFirstMeshYouCanFindIn(child);
                if (m) return m;
            }
        } else {
            return meshes[0].mesh.get();
        }

        return nullptr;
    }

    PAX_PROPERTY_IMPL(Meshfold)

    Meshfold::Meshfold() {
        /*
        portals.resize(2);

        portals[0].target = 1;
        portals[1].target = 0;

        portals[0].from = {40,  -50};
        portals[0].to   = {130, 50};

        portals[1].from = {-70, -100};
        portals[1].to   = {-80, 100};
        //portals[1].direction = Portal::LEFT;

        //portals[1].from = {90,  50};
        //portals[1].to   = {90, -50};
         //*/
    }

    Meshfold::~Meshfold() = default;

    ClassMetadata Meshfold::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(backgroundShader)).flags = Field::IsMandatory | EngineFieldFlags::IsResource;
        m.add(paxfieldof(asset)).flags = Field::IsMandatory | EngineFieldFlags::IsResource;
        return m;
    }

    void Meshfold::created() {}

    void Meshfold::createPortalsFromAsset() {
        //PAX_LOG_DEBUG(Log::Level::Info, "Generating Portals from Asset:");
        //asset->print("");

        Mesh * mesh = getFirstMeshYouCanFindIn(asset);
        if (!mesh) {
            PAX_THROW_RUNTIME_ERROR("Asset does not contain any mesh!");
        }
        if (mesh->isUploaded()) {
            PAX_THROW_RUNTIME_ERROR("Given mesh is already uploaded!");
        }

        glm::vec2 worldSize = getOwner()->get<WorldSize>()->getSize2D();

        PortalGenerator generator(mesh);
        glm::mat3 portalTrafo(0);
        portalTrafo[0][0] = worldSize.x;
        portalTrafo[1][1] = -worldSize.y;
        portalTrafo[2] = glm::vec3(-0.5f * worldSize.x, 0.5f * worldSize.y, 1);
        portals = generator.computePortals(portalTrafo);
        asset->upload();
    }

    void Meshfold::attached(PAX::World &world) {
        Services::GetEventService().add<KeyPressedEvent, Meshfold, &Meshfold::onKeyDown>(this);

        createPortalsFromAsset();
        drawPortalPresenter();
        portalPresenter.getTransformation().position() = {0, 0, -999};
        portalPresenter.get<SpriteGraphics>()->setShader(backgroundShader);
        world.spawn(&backgroundPresenter);

        resizeBackground();
    }

    void Meshfold::detached(PAX::World &world) {
        world.despawn(&portalPresenter);
        world.despawn(&backgroundPresenter);

        Services::GetEventService().remove<KeyPressedEvent, Meshfold, &Meshfold::onKeyDown>(this);
    }

    void Meshfold::drawPortalPresenter() {
        World * world = getOwner();
        if (!world) return;

        glm::vec2 size = world->get<WorldSize>()->getSize2D();
        glm::vec2 halfsize = 0.5f * size;
        Image background(size.x,  size.y);

        glm::vec2 halfCornerSize = {3, 3};
        const static float PortalNormalLength = 15.f;

        //background.fillRect({0, 0}, {size.x - 1, size.y - 1}, Colours::White);

        /// Set Portal Colours
        std::vector<Colour> portalColour(portals.size(), Colour(0));
        {
            RandomColourPalette colourPalette;
            std::vector<bool> portalColourSet(portals.size(), false);

            for (size_t i = 0; i < portals.size(); ++i) {
                if (!portalColourSet[i]) {
                    Colour colour = colourPalette.getNext(); // get from palette

                    portalColour[i] = colour;
                    portalColourSet[i] = true;

                    portalColour[portals[i].target] = colour;
                    portalColourSet[portals[i].target] = true;
                }
            }
        }

        /// draw portals
        for (size_t i = 0; i < portals.size(); ++i) {
            const Portal & p = portals.at(i);

            glm::vec2 from = halfsize + p.from;
            glm::vec2   to = halfsize + p.to;
            glm::vec2 normal = p.normal();
            from.y = size.y - from.y;
            to.y = size.y - to.y;
            normal.y = -normal.y;

            // draw normal
            glm::vec2 normalStart = from + 0.5f * (to - from);
            background.drawLine(normalStart, normalStart + (PortalNormalLength * normal), Colours::Green);

            // draw portal
            background.drawLine(from, to, portalColour.at(i));

            // draw corners
            background.fillRect(from - halfCornerSize, from + halfCornerSize, Colours::Red);
            background.fillRect(to - halfCornerSize, to + halfCornerSize, Colours::Red);
        }

        SpriteGraphics * g = portalPresenter.get<SpriteGraphics>();
        std::shared_ptr<Texture> tex = background.toGPUTexture();
        if (g) {
            g->setTexture(tex);
        } else {
            g = new (GameEntity::GetPropertyAllocator().allocate<SpriteGraphics>()) SpriteGraphics(tex);
            portalPresenter.add(g);
        }
    }

    void Meshfold::setBackground(const std::shared_ptr<Texture> &backgroundImage) {
        backgroundPresenter.add(new (GameEntity::GetPropertyAllocator().allocate<SpriteGraphics>()) SpriteGraphics(backgroundImage));
        backgroundPresenter.getTransformation().position() = {0, 0, -1000};
        backgroundPresenter.get<SpriteGraphics>()->setShader(backgroundShader);
        resizeBackground();
    }

    void Meshfold::resizeBackground() {
        Size * s = backgroundPresenter.get<Size>();

        if (getOwner() && s) {
            WorldSize *w = getOwner()->get<WorldSize>();
            glm::vec3 backgroundScale = glm::vec3(w->getSize2D().x, w->getSize2D().y, 1);
            backgroundScale /= s->getSizeUnscaled();
            backgroundScale.z = 1;
            backgroundPresenter.getTransformation().setScale(backgroundScale);
        }
    }

    void Meshfold::onKeyDown(KeyPressedEvent & e) {
        if (!e.repeated && e.button == Key::F1 && getOwner()) {
            World * w = getOwner();
            if (portalPresenter.getWorld()) {
                w->despawn(&portalPresenter);
            } else {
                w->spawn(&portalPresenter);
            }
        }
    }

    const std::vector<Portal> & Meshfold::getPortals() const {
        return portals;
    }

    Meshfold::Transition Meshfold::traceRay(const glm::vec2 & p0, const glm::vec2 & d0) {
#if PAX_MESHFOLD_PORTAL_SAFETY_OFFSET
        static const float PortalTraverseSafetyGap = 1;//px
#endif

        Transition ret(p0, d0);

        if (glm::length2(d0) == 0) return ret;

        glm::vec2 p = p0;
        glm::vec2 d = d0;
        glm::vec2 normD = glm::normalize(d);
        float totalScale = 1.0f;
        float distanceToTravel = glm::length(d);
        float distanceAfterPortal = 1.f;
        int flip = 1;

        bool parallel;
        Portal * nearestIntersectedPortal;
        float distance_p_intersection; // p to hitpoint

#if PAX_MESHFOLD_MULTI_PORTAL
        while (distanceToTravel > 0) {
#endif
            nearestIntersectedPortal = nullptr;
            distance_p_intersection = 1.f;

            // Find the next portal we have to traverse
            for (Portal & portal : portals) {
                parallel = false;
                const glm::vec2 intersection = portal.intersect(p, d, parallel);

                if (!parallel
                    && 0.f <= intersection.x && intersection.x <= 1.f
                    && 0.f <  intersection.y && intersection.y <= distance_p_intersection)
                {
                    distance_p_intersection = intersection.y;
                    nearestIntersectedPortal = &portal;
                }
            }

            // If there is a portal in our way, go through it.
            if (nearestIntersectedPortal) {
                Portal & source = *nearestIntersectedPortal;
                Portal & target = portals.at(source.target);

                const glm::mat2 sourceSpace = source.space();
                const glm::mat2 targetSpace = target.space();
                const glm::mat2 teleport = targetSpace * sourceSpace;

                const glm::vec2 oldP = p;
                p = target.from + teleport * (oldP - source.from);
                normD = target.from + teleport * (oldP + normD - source.from) - p;

                // account for different portal sizes:
                //p += distance_portal_intersection * (target.to - target.from);
#if PAX_MESHFOLD_CONSIDER_PORTAL_SIZE
                const float scale = glm::length(target.to - target.from) / glm::length(source.to - source.from);
                const glm::mat2 scaleFix = {
                        {scale, 0}, {0, 1.f}
                };
                p = target.from + targetSpace * scaleFix * sourceSpace * (oldP - source.from);
                totalScale *= scale;
#endif

                distanceAfterPortal -= distance_p_intersection;
                float minimumWalk = distance_p_intersection  * glm::length(d);
#if PAX_MESHFOLD_PORTAL_SAFETY_OFFSET
                // We move the point a bit away from the target portal.
                // Otherwise, we are directly sent back and start an infinite portal journey.
                float entryAngle = glm::angle(normD, targetSpace[0]); // targetSpace[0] is the portal vector (to - from)
                minimumWalk += PortalTraverseSafetyGap / sin(entryAngle);
                p += minimumWalk * normD;
#endif
                distanceToTravel -= minimumWalk;
                d = std::max(distanceToTravel, 0.f) * normD;

                flip *= source.direction * target.direction;
            }
            else {
#if PAX_MESHFOLD_MULTI_PORTAL
                distanceToTravel = 0;
#else
                distanceAfterPortal = 0;
#endif
            }
#if PAX_MESHFOLD_MULTI_PORTAL
        }
#endif

        ret.position = p + d;
        ret.direction = normD;
        ret.scale = totalScale;
        ret.distanceTraveledAfterPortal = std::max(0.0f, distanceAfterPortal);
        ret.lastPortal = nearestIntersectedPortal;
        ret.flip = flip;
        return ret;
    }
}