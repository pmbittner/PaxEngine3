//
// Created by Paul Bittner on 28.01.2021.
//

#ifndef MESHFOLD_JSONSHAPE2DPARSER_H
#define MESHFOLD_JSONSHAPE2DPARSER_H

#include <polypropylene/serialisation/json/JsonParser.h>
#include "../shape/Shape2D.h"

PAX_DECLARE_JSONPARSER_FOR(std::shared_ptr<Physics::Shape2D>)

#endif //MESHFOLD_JSONSHAPE2DPARSER_H
