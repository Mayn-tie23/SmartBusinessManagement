#include "Product.h"
#include <iostream>
#include <fstream>
#include <sstream>

Product::Product(int id, std::string name, double price, int quantity)
	: id(id), name(name), price(price), quantity(quantity) {}

int Product::getId() const { return id; }
std::string Product::getName() const { return name; }
double Product::getPrice() const { return price; }
int Product::getQuantity() const { return quantity; }

void Product::addStock(int amount) {
	if (amount > 0) {
		quantity += amount;
	}
}

bool Product::removeStock(int amount) {
	if (amount > 0 && quantity >= amount) {
		quantity -= amount;
		return true;
	}
	return false;
}
bool Product::isLowStock() const {
	return quantity <= 5;
}

void saveInventoryToCSV(const std::vector<Product>& inventory, const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error: Could not open file for writing.\n";
        return;
    }

    file << "ID,Name,Price,Quantity\n";

 
    for (const auto& product : inventory) {
        file << product.getId() << ","
            << product.getName() << ","
            << product.getPrice() << ","
            << product.getQuantity() << "\n";
    }

    file.close();
    std::cout << "Success: Inventory saved to " << filename << "\n";
}
std::vector<Product> loadInventoryFromCSV(const std::string& filename) 
{
    std::vector<Product> inventory;
    std::ifstream file(filename);

if (!file.is_open()) {
    std::cout << "No inventory file found. Starting fresh.\n";
    return inventory;
}

std::string line;

std::getline(file, line);


while (std::getline(file, line)) {
    if (line.empty()) continue; 

    std::stringstream ss(line);
    std::string idStr, name, priceStr, qtyStr;

  
    std::getline(ss, idStr, ',');
    std::getline(ss, name, ',');
    std::getline(ss, priceStr, ',');
    std::getline(ss, qtyStr, ',');

    
    int id = std::stoi(idStr);
    double price = std::stod(priceStr);
    int qty = std::stoi(qtyStr);

    inventory.push_back(Product(id, name, price, qty));
}

file.close();
std::cout << "Successfully loaded " << inventory.size() << " products from " << filename << "\n";
return inventory;
}