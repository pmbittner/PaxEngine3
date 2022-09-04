//
// Created by Paul on 04.09.2022.
//

#ifndef PAXENGINE3_IMGUIUNIFORMDETECTOR_H
#define PAXENGINE3_IMGUIUNIFORMDETECTOR_H

#include "paxopengl/glslpreprocessor/GLSLPreprocessor.h"
#include "polypropylene/event/EventHandler.h"

#include "Variable.h"

namespace PAX {
    namespace Imgui {
        class ImguiUniformDetector : public OpenGL::GLSLPreprocessor {
        public:
            EventHandler<Variables&> OnUniformsDetected;

            ~ImguiUniformDetector() override;
            std::string preprocess(const Path & codeFile, const std::string& code) override;
        };
    }
}

#endif //PAXENGINE3_IMGUIUNIFORMDETECTOR_H
