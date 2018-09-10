//
// Created by Paul on 06.07.2017.
//

#ifndef PAXENGINE3_CSVROW_H
#define PAXENGINE3_CSVROW_H
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// customized
// http://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c

namespace PAX {
    namespace Util {
        class CSVRow {
        public:
            CSVRow(char separator = ';');

            std::string const &operator[](std::size_t index) const;
            std::size_t size() const;
            void readNextRow(std::istream &str);

        private:
            std::vector<std::string> m_data;
            char separator;
        };

        std::istream& operator>>(std::istream& str, CSVRow& data);
    }
}

#endif //PAXENGINE3_CSVROW_H
