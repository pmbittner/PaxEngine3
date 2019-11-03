//
// Created by Paul on 03.11.2019.
//

#ifndef PAXENGINE3_TAG_H
#define PAXENGINE3_TAG_H

#include <string>

namespace PAX {
    using Tag = std::string;


    class Tags {
    public:
#define PAX_DEFAULT_TAG(name) static constexpr const char* name = #name;

        PAX_DEFAULT_TAG(Player)
        PAX_DEFAULT_TAG(PlayerSpawn)
        PAX_DEFAULT_TAG(Enemy)
        PAX_DEFAULT_TAG(EnemySpawn)
        PAX_DEFAULT_TAG(Camera)

#undef PAX_DEFAULT_TAG
    };

}

#endif //PAXENGINE3_TAG_H
