//
// Created by Bittner on 17/07/2019.
//

#ifndef PAXENGINE3_UPDATEOPTIONS_H
#define PAXENGINE3_UPDATEOPTIONS_H

namespace PAX {
    class UpdateOptions {
    public:
        const float dt;
        const float actual_dt;

        UpdateOptions(float dt, float actual_dt);
    };
}

#endif //PAXENGINE3_UPDATEOPTIONS_H
