//
// Created by Paul Bittner on 21.03.2020.
//

#ifndef PAXENGINE3_OPENGLPOINTCLOUDSETTINGS_H
#define PAXENGINE3_OPENGLPOINTCLOUDSETTINGS_H

#include <paxcore/rendering/config/PointCloudSettings.h>

namespace PAX {
    namespace OpenGL {
        class OpenGLPointCloudSettings : public PointCloudSettings {
        public:
            void initialize();
            void setPointSize(float pointSize) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLPOINTCLOUDSETTINGS_H
