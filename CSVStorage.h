
#pragma once

#include <string>
#include <vector>

class CSVStorage {
public:
    static bool writeRows(
        const std::string& filename,
        const std::vector<std::vector<std::string>>& rows
    );

    static std::vector<std::vector<std::string>>
    readRows(const std::string& filename);
};
