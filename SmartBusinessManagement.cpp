#include <iostream>
#include <vector>
#include "Product.h"

int main() {
    std::cout << "--- Testing CSV Saving ---\n\n";


    std::vector<Product> myInventory;

    
    myInventory.push_back(Product(101, "Coffee Beans", 15.50, 10));
    myInventory.push_back(Product(102, "Paper Cups", 5.00, 100));
    myInventory.push_back(Product(103, "Oat Milk", 4.25, 3));

   
    saveInventoryToCSV(myInventory, "inventory.csv");

    return 0;
}
