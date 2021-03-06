//
// Created by Paul Bittner on 21.03.2020.
//

#ifndef PAXENGINE3_POINTCLOUDSETTINGS_H
#define PAXENGINE3_POINTCLOUDSETTINGS_H

#include <paxcore/rendering/data/Shader.h>

namespace PAX {
    class PointCloudSettings {
        float pointSize = 1;

    public:
        virtual ~PointCloudSettings() = 0;

        virtual void init(Shader * shader);

        virtual void setPointSize(float pointSize);
        float getPointSize();
    };
}

#endif //PAXENGINE3_POINTCLOUDSETTINGS_H
