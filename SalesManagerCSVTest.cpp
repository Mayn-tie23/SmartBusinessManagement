
#include "SalesManager.h"
#include <iostream>
#include <cassert>

int main() {

    InventoryManager inventory;

    inventory.addProduct(Product(101, "Rice", 15.0, 20));
    inventory.addProduct(Product(102, "Sugar", 10.0, 30));

    SalesManager manager(inventory);

    Sale sale1(1001, 101, 4, 15.0, "2026-11-19");
    Sale sale2(1002, 102, 3, 10.0, "2026-11-19");

    // Record sales
    assert(manager.recordSale(sale1));
    assert(manager.recordSale(sale2));

    assert(manager.calculateRevenue() == 90.0);

    // Save sales
    assert(manager.saveToCSV("sales.csv"));

    // Create another manager and load saved sales
    SalesManager loadedManager(inventory);

    assert(loadedManager.loadFromCSV("sales.csv"));

    // Verify loaded records
    assert(loadedManager.getSales().size() == 2);
    assert(loadedManager.calculateRevenue() == 90.0);

    assert(loadedManager.getSales()[0].getSaleId() == 1001);
    assert(loadedManager.getSales()[1].getSaleId() == 1002);

    std::cout << "Sales recording passed.\n";
    std::cout << "Sales CSV saving passed.\n";
    std::cout << "Sales CSV loading passed.\n";
    std::cout << "Transaction details verified.\n";
    std::cout << "Revenue after loading: $"
              << loadedManager.calculateRevenue() << "\n";

    std::cout << "\nAll Sales CSV tests passed!\n";

    return 0;
}
