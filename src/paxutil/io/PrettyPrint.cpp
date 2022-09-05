//
// Created by Paul Bittner on 05.09.2022.
//

#include <iomanip> // std::setw
#include "paxutil/io/PrettyPrint.h"

namespace PAX {
    namespace Util {
        void printWithLineNumbersTo(std::stringstream & target, const std::string & text) {
            printWithLineNumbersTo(target, text, 4);
        }

        void printWithLineNumbersTo(std::stringstream & target, const std::string & text, unsigned int maxLineNoDigits) {
            std::stringstream textStream(text);
            std::string line;
            int lineNo = 0;
            while (std::getline(textStream, line, '\n')) {
                target << std::setw(4) << std::fixed << lineNo << "| " << line << std::endl;
                ++lineNo;
            }
        }
    }
}