
#include "CSVStorage.h"
#include <fstream>
#include <sstream>

bool CSVStorage::writeRows(
    const std::string& filename,
    const std::vector<std::vector<std::string>>& rows
) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    for (const auto& row : rows) {
        for (size_t i = 0; i < row.size(); ++i) {
            if (i > 0) {
                file << ",";
            }

            file << "\"" ;

            for (char c : row[i]) {
                if (c == '"') {
                    file << "\"\"";
                } else {
                    file << c;
                }
            }

            file << "\"";
        }

        file << "\n";
    }

    return file.good();
}

std::vector<std::vector<std::string>>
CSVStorage::readRows(const std::string& filename) {

    std::vector<std::vector<std::string>> rows;
    std::ifstream file(filename);

    if (!file.is_open()) {
        return rows;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::string value;
        bool insideQuotes = false;

        for (size_t i = 0; i < line.size(); ++i) {
            char c = line[i];

            if (c == '"') {
                if (insideQuotes &&
                    i + 1 < line.size() &&
                    line[i + 1] == '"') {
                    value += '"';
                    ++i;
                } else {
                    insideQuotes = !insideQuotes;
                }
            }
            else if (c == ',' && !insideQuotes) {
                row.push_back(value);
                value.clear();
            }
            else {
                value += c;
            }
        }

        row.push_back(value);
        rows.push_back(row);
    }

    return rows;
}
