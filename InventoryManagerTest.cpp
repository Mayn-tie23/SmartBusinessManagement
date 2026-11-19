
#include "InventoryManager.h"
#include <iostream>
#include <cassert>

int main() {
    InventoryManager inventory;

    Product rice(101, "Rice", 15.0, 20);
    Product sugar(102, "Sugar", 10.0, 30);

    // Test adding products
    assert(inventory.addProduct(rice));
    assert(inventory.addProduct(sugar));

    // Test duplicate product prevention
    assert(!inventory.addProduct(rice));

    // Test product searching
    Product* found = inventory.findProduct(101);

    assert(found != nullptr);
    assert(found->getName() == "Rice");

    // Test stock updating
    assert(inventory.updateStock(101, 15));
    assert(inventory.findProduct(101)->getQuantity() == 15);

    // Test removing products
    assert(inventory.removeProduct(102));
    assert(inventory.findProduct(102) == nullptr);

    // Test total products
    assert(inventory.getProducts().size() == 1);

    std::cout << "Products added successfully.\n";
    std::cout << "Duplicate prevention passed.\n";
    std::cout << "Product search passed.\n";
    std::cout << "Stock update passed.\n";
    std::cout << "Product removal passed.\n";
    std::cout << "\nAll InventoryManager tests passed!\n";

    return 0;
}
