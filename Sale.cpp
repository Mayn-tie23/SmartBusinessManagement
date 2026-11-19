
#include "Sale.h"

Sale::Sale(int saleId, int productId, int quantity,
           double unitPrice, std::string date)
    : saleId(saleId),
      productId(productId),
      quantity(quantity),
      unitPrice(unitPrice),
      date(date) {
}

int Sale::getSaleId() const {
    return saleId;
}

int Sale::getProductId() const {
    return productId;
}

int Sale::getQuantity() const {
    return quantity;
}

double Sale::getUnitPrice() const {
    return unitPrice;
}

std::string Sale::getDate() const {
    return date;
}

double Sale::getTotal() const {
    return quantity * unitPrice;
}
