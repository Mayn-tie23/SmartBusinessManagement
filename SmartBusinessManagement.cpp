#include <iostream>
#include <vector>
#include "Product.h"

int main() {
    std::cout << "--- Testing CSV Loading ---\n\n";

    
    std::vector<Product> myInventory = loadInventoryFromCSV("inventory.csv");

    
    if (!myInventory.empty()) {
        std::cout << "\nInventory List:\n";
        for (const auto& p : myInventory) {
            std::cout << "ID: " << p.getId()
                << " | Name: " << p.getName()
                << " | Price: $" << p.getPrice()
                << " | Stock: " << p.getQuantity() << "\n";
        }
    }

    return 0;
}