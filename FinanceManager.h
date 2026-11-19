
#pragma once

#include "Transaction.h"
#include <vector>
#include <string>

class FinanceManager {
private:
    std::vector<Transaction> transactions;

public:
    bool addTransaction(const Transaction& transaction);

    double calculateIncome() const;
    double calculateExpenses() const;
    double calculateNetProfit() const;

    const std::vector<Transaction>& getTransactions() const;

    bool saveToCSV(const std::string& filename) const;
    bool loadFromCSV(const std::string& filename);
};

