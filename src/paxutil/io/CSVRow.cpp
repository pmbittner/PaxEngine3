//
// Created by Paul on 06.07.2017.
//

#include <paxutil/io/CSVRow.h>

PAX::Util::CSVRow::CSVRow(char separator) : separator(separator) {}

void PAX::Util::CSVRow::readNextRow(std::istream &str) {
    std::string line;
    std::getline(str, line);

    std::stringstream lineStream(line);
    std::string cell;

    m_data.clear();
    while (std::getline(lineStream, cell, separator)) {
        m_data.push_back(cell);
    }
    // This checks for a trailing comma with no data after it.
    if (!lineStream && cell.empty()) {
        // If there was a trailing comma then add an empty element.
        m_data.push_back("");
    }
}

std::string const& PAX::Util::CSVRow::operator[](std::size_t index) const {
    return m_data[index];
}

std::size_t PAX::Util::CSVRow::size() const {
    return m_data.size();
}

std::istream& PAX::Util::operator>>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}