#pragma once
#include <string>
#include <vector>

class Product {
private:
	int id;
	std::string name;
	double price;
	int quantity;

public:

		Product(int id, std::string name, double price, int quantity);

	int getId() const;
	std::string getName() const;
	double getPrice() const;
	int getQuantity() const;

	void addStock(int amaount);
	bool removeStock(int amount);
	bool isLowStock() const;
};

void saveInventoryToCSV(const std::vector<Product>& inventory, const std::string& filename);
