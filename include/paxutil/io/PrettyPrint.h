//
// Created by Paul Bittner on 05.09.2022.
//

#ifndef PAXENGINE3_PRETTYPRINT_H
#define PAXENGINE3_PRETTYPRINT_H

#include <sstream>

namespace PAX {
    namespace Util {
        void printWithLineNumbersTo(std::stringstream & target, const std::string & text);
        void printWithLineNumbersTo(std::stringstream & target, const std::string & text, unsigned int maxLineNoDigits);
    }
}

#endif //PAXENGINE3_PRETTYPRINT_H
