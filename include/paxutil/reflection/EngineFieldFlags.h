//
// Created by Bittner on 02.01.2020.
//

#ifndef PAXENGINE3_ENGINEFIELDFLAGS_H
#define PAXENGINE3_ENGINEFIELDFLAGS_H

#include <polypropylene/reflection/Field.h>

namespace PAX::EngineFieldFlags {
    constexpr FieldFlag IsResource = Field::CustomFlagsBegin;
    constexpr FieldFlag IsList = IsResource * 2;
}

#endif //PAXENGINE3_ENGINEFIELDFLAGS_H
