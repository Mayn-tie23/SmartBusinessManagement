
#include "FinanceManager.h"
#include "CSVStorage.h"

#include <cmath>
#include <string>
#include <exception>

bool FinanceManager::addTransaction(const Transaction& transaction) {
    if (transaction.getId() <= 0 ||
        !std::isfinite(transaction.getAmount()) ||
        transaction.getAmount() < 0 ||
        transaction.getCategory().empty() ||
        transaction.getDate().empty()) {
        return false;
    }

    for (const Transaction& existing : transactions) {
        if (existing.getId() == transaction.getId()) {
            return false;
        }
    }

    transactions.push_back(transaction);
    return true;
}

double FinanceManager::calculateIncome() const {
    double total = 0.0;

    for (const Transaction& transaction : transactions) {
        if (transaction.getType() == TransactionType::Income) {
            total += transaction.getAmount();
        }
    }

    return total;
}

double FinanceManager::calculateExpenses() const {
    double total = 0.0;

    for (const Transaction& transaction : transactions) {
        if (transaction.getType() == TransactionType::Expense) {
            total += transaction.getAmount();
        }
    }

    return total;
}

double FinanceManager::calculateNetProfit() const {
    return calculateIncome() - calculateExpenses();
}

const std::vector<Transaction>&
FinanceManager::getTransactions() const {
    return transactions;
}

bool FinanceManager::saveToCSV(const std::string& filename) const {
    std::vector<std::vector<std::string>> rows;

    rows.push_back({
        "ID", "Type", "Amount", "Category", "Date"
    });

    for (const Transaction& transaction : transactions) {
        std::string type =
            transaction.getType() == TransactionType::Income
            ? "Income" : "Expense";

        rows.push_back({
            std::to_string(transaction.getId()),
            type,
            std::to_string(transaction.getAmount()),
            transaction.getCategory(),
            transaction.getDate()
        });
    }

    return CSVStorage::writeRows(filename, rows);
}

bool FinanceManager::loadFromCSV(const std::string& filename) {
    std::vector<std::vector<std::string>> rows =
        CSVStorage::readRows(filename);

    if (rows.empty() ||
        rows[0] != std::vector<std::string>{
            "ID", "Type", "Amount", "Category", "Date"
        }) {
        return false;
    }

    std::vector<Transaction> loadedTransactions;

    try {
        for (size_t i = 1; i < rows.size(); ++i) {
            if (rows[i].size() != 5) {
                return false;
            }

            int id = std::stoi(rows[i][0]);
            double amount = std::stod(rows[i][2]);

            TransactionType type;

            if (rows[i][1] == "Income") {
                type = TransactionType::Income;
            } else if (rows[i][1] == "Expense") {
                type = TransactionType::Expense;
            } else {
                return false;
            }

            if (id <= 0 || !std::isfinite(amount) || amount < 0 ||
                rows[i][3].empty() || rows[i][4].empty()) {
                return false;
            }

            for (const Transaction& existing : loadedTransactions) {
                if (existing.getId() == id) {
                    return false;
                }
            }

            loadedTransactions.emplace_back(
                id, type, amount, rows[i][3], rows[i][4]
            );
        }
    } catch (const std::exception&) {
        return false;
    }

    transactions = std::move(loadedTransactions);
    return true;
}
