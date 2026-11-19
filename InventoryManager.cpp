
#include "InventoryManager.h"

bool InventoryManager::addProduct(const Product& product) {
    if (findProduct(product.getId()) != nullptr) {
        return false;
    }

    products.push_back(product);
    return true;
}

bool InventoryManager::removeProduct(int id) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->getId() == id) {
            products.erase(it);
            return true;
        }
    }

    return false;
}

bool InventoryManager::updateStock(int id, int quantity) {
    Product* product = findProduct(id);

    if (product == nullptr || quantity < 0) {
        return false;
    }

    int difference = quantity - product->getQuantity();

    if (difference > 0) {
        product->addStock(difference);
    } else if (difference < 0) {
        return product->removeStock(-difference);
    }

    return true;
}

Product* InventoryManager::findProduct(int id) {
    for (auto& product : products) {
        if (product.getId() == id) {
            return &product;
        }
    }

    return nullptr;
}

const std::vector<Product>& InventoryManager::getProducts() const {
    return products;
}

bool InventoryManager::saveToCSV(const std::string& filename) const {
    saveInventoryToCSV(products, filename);
    return true;
}

bool InventoryManager::loadFromCSV(const std::string& filename) {
    products = loadInventoryFromCSV(filename);
    return true;
}
