
#include "Transaction.h"

Transaction::Transaction(int id, TransactionType type,
                         double amount, std::string category,
                         std::string date)
    : id(id),
      type(type),
      amount(amount),
      category(category),
      date(date) {
}

int Transaction::getId() const {
    return id;
}

TransactionType Transaction::getType() const {
    return type;
}

double Transaction::getAmount() const {
    return amount;
}

std::string Transaction::getCategory() const {
    return category;
}

std::string Transaction::getDate() const {
    return date;
}
