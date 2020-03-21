//
// Created by Paul Bittner on 21.03.2020.
//

#include <paxcore/rendering/config/PointCloudSettings.h>
#include <polypropylene/log/Errors.h>

namespace PAX {
    PointCloudSettings::~PointCloudSettings() = default;

    void PointCloudSettings::setPointSize(float pointSize) {
        if (pointSize <= 0) {
            PAX_THROW_RUNTIME_ERROR("Point size cannot be smaller or equal to 0!");
        }
        this->pointSize = pointSize;
    }

    float PointCloudSettings::getPointSize() {
        return pointSize;
    }
}