//
// Created by Gordon on 16.05.2017.
//

#include <paxcore/rendering/camera/Camera.h>
#include <paxcore/entity/Entity.h>
#include <paxutil/macros/MacroIncludes.h>
#include <paxcore/service/Services.h>
#include <paxcore/rendering/factory/ViewportFactory.h>
#include <paxcore/rendering/camera/PixelScreenProjection.h>

namespace PAX {
    PAX_PROPERTY_SOURCE(PAX::Camera, PAX_PROPERTY_IS_CONCRETE)

    Camera * Camera::createFromProvider(PAX::ContentProvider & provider) {
        // load viewport
        ViewportFactory * vpFactory = Services::GetFactoryService().get<ViewportFactory>();
        std::shared_ptr<Viewport> vp;

        if (const auto & vp_x = provider.get<int>("viewport_x")) {
            int x = vp_x.value();
            int y = provider.require<int>("viewport_y");
            int width = provider.require<int>("viewport_width");
            int height = provider.require<int>("viewport_height");
            std::string resizePolicyString = provider.require<std::string>("viewport_resizepolicy");
            Viewport::ResizePolicy resizePolicy =
                    resizePolicyString == "Relative" ?
                    Viewport::ResizePolicy::Relative : Viewport::ResizePolicy::Absolute;

            vp = vpFactory->create(x, y, width, height, resizePolicy);
        } else {
            vp = vpFactory->create();
        }

        // TODO: Make this extensible somehow.
        // load projection
        std::string projName = provider.require<std::string>("projection");
        std::shared_ptr<Projection> proj;
        if (projName == "Perspective") {
            proj = std::make_shared<PerspectiveProjection>();
        } else if (projName == "PixelScreen") {
            proj = std::make_shared<PixelScreenProjection>();
        } else {
            PAX_LOG(PAX::Log::Level::Error, "Could not resolve projection type " << projName);
        }

        return new Camera(vp, proj);
    }

    void Camera::initializeFromProvider(PAX::ContentProvider & provider) {
        Super::initializeFromProvider(provider);

        if (auto syncResolutions = provider.get<bool>("syncProjectionResolutionToViewportResolution")) {
            this->syncProjectionResolutionToViewportResolution = syncResolutions.value();
        }

        if (!this->syncProjectionResolutionToViewportResolution) {
            glm::ivec2 resolution = projection->getResolution();
            if (auto projection_resolution_width = provider.get<int>("projection_resolution_width")) {
                resolution.x = projection_resolution_width.value();
            }
            if (auto projection_resolution_height = provider.get<int>("projection_resolution_height")) {
                resolution.y = projection_resolution_height.value();
            }
            projection->setResolution(resolution);
        }
    }

    Camera::Camera(const std::shared_ptr<Viewport> & viewport, const std::shared_ptr<Projection> & projection) : viewport(viewport), projection(projection) {
        PAX_ASSERT_NOT_NULL(viewport, "Viewport can't be null!");
        PAX_ASSERT_NOT_NULL(projection, "Projection can't be null!");

        viewport->WidthChanged.add<Camera, &Camera::onViewportWidthChanged>(this);
        viewport->HeightChanged.add<Camera, &Camera::onViewportHeightChanged>(this);

        projection->setResolution({viewport->getWidth(), viewport->getHeight()});
    }

    void Camera::render(RenderOptions &renderOptions) {
        renderOptions.setCamera(this);
        renderOptions.setViewMatrix(getViewTransform());
        renderOptions.setProjectionMatrix(projection->toMatrix());

        viewport->apply();
        SceneGraph::render(renderOptions);
    }

    const glm::mat4 & Camera::getViewTransform() {
        Entity *owner = getOwner();

        if (owner) {
            Transformation &transform = owner->getTransformation();
            viewMatrix = transform.getWorldMatrix();
            // extracting upper left 3x3 part of the mat4
            glm::mat3 rotationMatrix(viewMatrix);
            // remove scaling
            /*
            for (int i = 0; i < 3; ++i) {
                rotationMatrix[i] = glm::normalize(rotationMatrix[i]);
            }//*/
            // invert the rotation (rotationMatrix is orthogonal => transpose = inverse)
            rotationMatrix = glm::transpose(rotationMatrix);
            // apply the rotation of the matrix to the displacement, as it isn't independent of the rotation,
            // meaning, that the look should rotate with its object
            glm::vec3 translation = rotationMatrix * glm::vec3(viewMatrix[3]);
            viewMatrix = glm::mat4(rotationMatrix);
            // invert translation
            viewMatrix[3] = glm::vec4(-translation, 1);
        } else {
            viewMatrix = glm::mat4(1.0f);
        }

        return viewMatrix;
    }

    void Camera::onViewportWidthChanged(int oldWidth, int newWidth) {
        if (syncProjectionResolutionToViewportResolution) {
            projection->setResolution({newWidth, projection->getResolution().y});
        }
    }

    void Camera::onViewportHeightChanged(int oldHeight, int newHeight) {
        if (syncProjectionResolutionToViewportResolution) {
            projection->setResolution({projection->getResolution().x, newHeight});
        }
    }

    std::shared_ptr<Viewport> Camera::getViewport() const {
        return viewport;
    }

    std::shared_ptr<Projection> Camera::getProjection() const {
        return projection;
    }

    void Camera::setSyncProjectionResolutionToViewportResolution(bool sync) {
        if (sync && !syncProjectionResolutionToViewportResolution) {
            // If sync is activated now (and wasn't before), update the projection resolution.
            projection->setResolution(viewport->getSize());
        }

        syncProjectionResolutionToViewportResolution = sync;
    }

    bool Camera::areProjectionResolutionToViewportResolutionSynced() const {
        return syncProjectionResolutionToViewportResolution;
    }
}