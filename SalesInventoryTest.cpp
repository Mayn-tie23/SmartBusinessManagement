
#include "SalesManager.h"
#include <iostream>
#include <cassert>

int main() {

    InventoryManager inventory;

    Product rice(101, "Rice", 15.0, 20);

    assert(inventory.addProduct(rice));

    SalesManager salesManager(inventory);

    Sale sale1(1001, 101, 5, 15.0, "2026-11-19");

    // Test successful sale
    assert(salesManager.recordSale(sale1));

    assert(inventory.findProduct(101)->getQuantity() == 15);

    // Test insufficient stock
    Sale sale2(1002, 101, 25, 15.0, "2026-11-19");

    assert(!salesManager.recordSale(sale2));

    assert(inventory.findProduct(101)->getQuantity() == 15);

    // Test duplicate sale ID
    assert(!salesManager.recordSale(sale1));

    // Test revenue
    assert(salesManager.calculateRevenue() == 75.0);

    std::cout << "Sale recorded successfully.\n";
    std::cout << "Inventory automatically updated.\n";
    std::cout << "Insufficient stock prevention passed.\n";
    std::cout << "Duplicate transaction prevention passed.\n";
    std::cout << "Total revenue: $"
              << salesManager.calculateRevenue() << "\n";

    std::cout << "\nAll Sales and Inventory integration tests passed!\n";

    return 0;
}
