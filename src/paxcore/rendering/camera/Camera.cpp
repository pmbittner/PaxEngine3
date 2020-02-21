//
// Created by Gordon on 16.05.2017.
//

#include <paxcore/rendering/camera/Camera.h>
#include <paxcore/gameentity/GameEntity.h>
#include <paxcore/service/Services.h>
#include <paxcore/rendering/factory/ViewportFactory.h>
#include <paxcore/rendering/camera/PixelScreenProjection.h>

namespace PAX {
    PAX_PROPERTY_IMPL(PAX::Camera)

    void Camera::init() {
        PAX_ASSERT_NOT_NULL(viewport, "Viewport not initialised!");
        PAX_ASSERT_NOT_NULL(projection, "Viewport not initialised!");

        viewport->WidthChanged.add<Camera, &Camera::onViewportWidthChanged>(this);
        viewport->HeightChanged.add<Camera, &Camera::onViewportHeightChanged>(this);

        projection->setResolution({viewport->getWidth(), viewport->getHeight()});

        if (syncProjectionResolutionToViewportResolution) {
            // FIXME?
        }
    }

    void Camera::created() {
        Super::created();
        init();
    }

    ClassMetadata Camera::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(viewport)).flags = Field::IsMandatory;
        m.add(paxfieldof(projection)).flags = Field::IsMandatory;
        m.add(paxfieldof(syncProjectionResolutionToViewportResolution));
        return m;
    }

    Camera::Camera() = default;

    Camera::Camera(Viewport * viewport, Projection * projection) : viewport(viewport), projection(projection) {
        init();
    }

    Camera::~Camera() {
        delete viewport;
        delete projection;
    }

    void Camera::render(RenderOptions &renderOptions) {
        renderOptions.setCamera(this);
        renderOptions.setViewMatrix(getViewTransform());
        renderOptions.setProjectionMatrix(projection->toMatrix());

        viewport->apply();
        SceneGraph::render(renderOptions);
    }

    const glm::mat4 & Camera::getViewTransform() {
        GameEntity *owner = getOwner();

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

    Viewport & Camera::getViewport() const {
        return *viewport;
    }

    Projection & Camera::getProjection() const {
        return *projection;
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