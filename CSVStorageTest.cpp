
#include "CSVStorage.h"
#include <iostream>
#include <cassert>

int main() {

    std::vector<std::vector<std::string>> rows = {
        {"1001", "Rice", "15.0", "20"},
        {"1002", "Brown Rice, Premium", "25.0", "10"},
        {"1003", "Sugar \"Premium\"", "10.0", "30"}
    };

    // Test saving
    assert(CSVStorage::writeRows("test.csv", rows));

    // Test loading
    auto loadedRows = CSVStorage::readRows("test.csv");

    assert(loadedRows.size() == 3);
    assert(loadedRows[0][1] == "Rice");
    assert(loadedRows[1][1] == "Brown Rice, Premium");
    assert(loadedRows[2][1] == "Sugar \"Premium\"");

    std::cout << "CSV saving passed.\n";
    std::cout << "CSV loading passed.\n";
    std::cout << "Comma handling passed.\n";
    std::cout << "Quotation mark handling passed.\n";

    std::cout << "\nAll CSVStorage tests passed!\n";

    return 0;
}
