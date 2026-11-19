
#pragma once

#include "Product.h"
#include <vector>
#include <string>

class InventoryManager {
private:
    std::vector<Product> products;

public:
    bool addProduct(const Product& product);
    bool removeProduct(int id);
    bool updateStock(int id, int quantity);
    Product* findProduct(int id);
    const std::vector<Product>& getProducts() const;

    bool saveToCSV(const std::string& filename) const;
    bool loadFromCSV(const std::string& filename);
};
