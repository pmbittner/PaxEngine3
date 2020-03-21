//
// Created by Paul on 30.06.2017.
//

#include <paxutil/math/Transformation.h>
#include <paxcore/rendering/RenderOptions.h>
#include <paxcore/rendering/Renderer.h>
#include <paxcore/world/World.h>
#include <paxcore/rendering/config/PointCloudSettings.h>

namespace PAX {
    bool ShaderOptions::pushShader(void *caller, Shader* shader, ShaderPriority priority) {
        PAX_ASSERT_NOT_NULL(shader, "Shader can't be null!");

        if (_shaders.empty() || _shaders.top()._priority == ShaderPriority::MUTABLE) {
            ShaderUsage usage;
            usage._priority = priority;
            usage._owner = caller;
            usage._shader = shader;
            _shaders.push(usage);

            shader->bind();

            return true;
        }

        return false;
    }

    bool ShaderOptions::popShader(void *caller) {
        if(caller == _shaders.top()._owner) {
            _shaders.top()._shader->unbind();
            _shaders.pop();

            if (!_shaders.empty())
                _shaders.top()._shader->bind();
        }

        return true;
    }

    Shader* ShaderOptions::getShader() {
        if (_shaders.empty())
            return nullptr;
        return _shaders.top()._shader;
    }

    RenderOptions::RenderOptions(const Renderer& renderer, float dt, float actualDt) :
    _renderer(renderer),
    _camera(nullptr),
    _world(nullptr),
    dt(dt),
    actual_dt(actualDt) {
    }

    PAX::Camera *PAX::RenderOptions::getCamera() const {
        return _camera;
    }

    void PAX::RenderOptions::setCamera(PAX::Camera *camera) {
        RenderOptions::_camera = camera;
    }
    
    World * RenderOptions::getWorld() const {
        return _world;
    }
    
    void RenderOptions::setWorld(World *world) {
        _world = world;
    }

    glm::mat4 & PAX::RenderOptions::getTransformationMatrix() {
        return _currentTransform;
    }

    void PAX::RenderOptions::setTransformationMatrix(const glm::mat4 &transform) {
        _currentTransform = transform;
        _renderer.OnTransformationChanged(*this);
    }

    glm::mat4& RenderOptions::getProjectionMatrix() {
        return _currentProjection;
    }

    void RenderOptions::setProjectionMatrix(const glm::mat4 &projection) {
        _currentProjection = projection;
    }

    glm::mat4& RenderOptions::getViewMatrix() {
        return _currentView;
    }

    void RenderOptions::setViewMatrix(const glm::mat4 &view) {
        _currentView = view;
    }

    ShaderOptions& PAX::RenderOptions::getShaderOptions() {
        return _shaderOptions;
    }

    float RenderOptions::getDeltaTime() const {
        return dt;
    }

    float RenderOptions::getActualDeltaTime() const {
        return dt;
    }

    void RenderOptions::setPointSize(float pointSize) {
        Services::Instance().get<PointCloudSettings>()->setPointSize(pointSize);
    }

    float RenderOptions::getPointSize() const {
        return Services::Instance().get<PointCloudSettings>()->getPointSize();
    }
}