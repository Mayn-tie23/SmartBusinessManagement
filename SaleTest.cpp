
#include "Sale.h"
#include <iostream>
#include <cassert>

int main() {
    Sale sale(1001, 101, 4, 15.0, "2026-11-19");

    assert(sale.getSaleId() == 1001);
    assert(sale.getProductId() == 101);
    assert(sale.getQuantity() == 4);
    assert(sale.getUnitPrice() == 15.0);
    assert(sale.getTotal() == 60.0);

    std::cout << "Sale ID: " << sale.getSaleId() << "\n";
    std::cout << "Product ID: " << sale.getProductId() << "\n";
    std::cout << "Quantity: " << sale.getQuantity() << "\n";
    std::cout << "Unit Price: $" << sale.getUnitPrice() << "\n";
    std::cout << "Total: $" << sale.getTotal() << "\n";

    std::cout << "\nAll Sale tests passed successfully!\n";

    return 0;
}
