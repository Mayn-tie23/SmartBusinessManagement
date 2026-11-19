
#pragma once

#include "Sale.h"
#include "InventoryManager.h"
#include <vector>
#include <string>

class SalesManager {
private:
    std::vector<Sale> sales;
    InventoryManager& inventory;

public:
    explicit SalesManager(InventoryManager& inventory);

    bool recordSale(const Sale& sale);

    double calculateRevenue() const;

    const std::vector<Sale>& getSales() const;

    bool saveToCSV(const std::string& filename) const;

    bool loadFromCSV(const std::string& filename);
};
