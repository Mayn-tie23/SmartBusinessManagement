
#pragma once

#include <string>

enum class TransactionType {
    Income,
    Expense
};

class Transaction {
private:
    int id;
    TransactionType type;
    double amount;
    std::string category;
    std::string date;

public:
    Transaction(int id, TransactionType type,
                double amount, std::string category,
                std::string date);

    int getId() const;
    TransactionType getType() const;
    double getAmount() const;
    std::string getCategory() const;
    std::string getDate() const;
};
