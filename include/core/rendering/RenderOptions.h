//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_RENDEROPTIONS_H
#define PAXENGINE3_RENDEROPTIONS_H

namespace PAX {
    class Camera;
    class Shader;

    class RenderOptions {
        Camera *_camera;
        Shader *_shader;

    public:
        RenderOptions();

        Camera *getCamera() const;
        void setCamera(Camera *camera);
        Shader *getShader() const;
        void setShader(Shader *shader);
    };
}

#endif //PAXENGINE3_RENDEROPTIONS_H
