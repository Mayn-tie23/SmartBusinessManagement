
#include "Product.h"
#include <iostream>
#include <stdexcept>

int failures = 0;

void check(bool condition, const char* test) {
    if (condition)
        std::cout << "[PASS] " << test << "\n";
    else {
        std::cout << "[FAIL] " << test << "\n";
        ++failures;
    }
}

int main() {
    Product rice(1, "Rice", 5.0, 10);

    check(rice.getId() == 1, "Product ID");
    check(rice.getName() == "Rice", "Product name");
    check(rice.getPrice() == 5.0, "Product price");
    check(rice.getQuantity() == 10, "Initial stock");

    rice.addStock(5);
    check(rice.getQuantity() == 15, "Add stock");

    check(rice.removeStock(3), "Remove stock");
    check(rice.getQuantity() == 12, "Stock updated");

    check(!rice.removeStock(100), "Reject insufficient stock");
    check(rice.getQuantity() == 12, "Stock unchanged");

    rice.addStock(-5);
    check(rice.getQuantity() == 12, "Reject negative stock addition");

    rice.removeStock(8);
    check(rice.isLowStock(), "Low-stock detection");

    std::vector<Product> products = { rice };
    saveInventoryToCSV(products, "inventory_test.csv");

    auto loaded = loadInventoryFromCSV("inventory_test.csv");

    check(loaded.size() == 1, "CSV loading");
    if (loaded.size() == 1) {
        check(loaded[0].getId() == 1, "CSV product ID");
        check(loaded[0].getQuantity() == 4, "CSV stock quantity");
    }

    std::cout << "\nTests failed: " << failures << "\n";
    return failures == 0 ? 0 : 1;
}
