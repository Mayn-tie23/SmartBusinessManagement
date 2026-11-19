
#pragma once

#include <string>

class Sale {
private:
    int saleId;
    int productId;
    int quantity;
    double unitPrice;
    std::string date;

public:
    Sale(int saleId, int productId, int quantity,
         double unitPrice, std::string date);

    int getSaleId() const;
    int getProductId() const;
    int getQuantity() const;
    double getUnitPrice() const;
    std::string getDate() const;

    double getTotal() const;
};
