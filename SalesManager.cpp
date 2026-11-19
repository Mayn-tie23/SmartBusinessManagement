
#include "SalesManager.h"
#include "CSVStorage.h"
#include <string>
#include <stdexcept>

SalesManager::SalesManager(InventoryManager& inventory)
    : inventory(inventory) {
}

bool SalesManager::recordSale(const Sale& sale) {
    Product* product = inventory.findProduct(sale.getProductId());

    if (product == nullptr ||
        sale.getQuantity() <= 0 ||
        product->getQuantity() < sale.getQuantity()) {
        return false;
    }

    for (const Sale& existingSale : sales) {
        if (existingSale.getSaleId() == sale.getSaleId()) {
            return false;
        }
    }

    if (!product->removeStock(sale.getQuantity())) {
        return false;
    }

    sales.push_back(sale);
    return true;
}

double SalesManager::calculateRevenue() const {
    double total = 0.0;

    for (const Sale& sale : sales) {
        total += sale.getTotal();
    }

    return total;
}

const std::vector<Sale>& SalesManager::getSales() const {
    return sales;
}

bool SalesManager::saveToCSV(const std::string& filename) const {
    std::vector<std::vector<std::string>> rows;

    rows.push_back({
        "SaleID", "ProductID", "Quantity",
        "UnitPrice", "Date"
    });

    for (const Sale& sale : sales) {
        rows.push_back({
            std::to_string(sale.getSaleId()),
            std::to_string(sale.getProductId()),
            std::to_string(sale.getQuantity()),
            std::to_string(sale.getUnitPrice()),
            sale.getDate()
        });
    }

    return CSVStorage::writeRows(filename, rows);
}

bool SalesManager::loadFromCSV(const std::string& filename) {
    auto rows = CSVStorage::readRows(filename);

    if (rows.empty() ||
        rows[0] != std::vector<std::string>{
            "SaleID", "ProductID", "Quantity",
            "UnitPrice", "Date"
        }) {
        return false;
    }

    std::vector<Sale> loadedSales;

    try {
        for (size_t i = 1; i < rows.size(); ++i) {
            if (rows[i].size() != 5) {
                return false;
            }

            int id = std::stoi(rows[i][0]);
            int productId = std::stoi(rows[i][1]);
            int quantity = std::stoi(rows[i][2]);
            double price = std::stod(rows[i][3]);

            if (id <= 0 || productId <= 0 ||
                quantity <= 0 || price < 0) {
                return false;
            }

            for (const Sale& existing : loadedSales) {
                if (existing.getSaleId() == id) {
                    return false;
                }
            }

            loadedSales.emplace_back(
                id, productId, quantity, price, rows[i][4]
            );
        }
    }
    catch (const std::exception&) {
        return false;
    }

    sales = std::move(loadedSales);
    return true;
}
