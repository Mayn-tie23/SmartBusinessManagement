
#include "FinanceManager.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include <cstdio>

int main() {
    FinanceManager finance;

    // Add income transactions
    assert(finance.addTransaction(
        Transaction(1, TransactionType::Income, 1500, "Sales", "2026-11-19")));

    assert(finance.addTransaction(
        Transaction(2, TransactionType::Income, 500, "Services", "2026-11-19")));

    // Add expense transactions
    assert(finance.addTransaction(
        Transaction(3, TransactionType::Expense, 600, "Rent", "2026-11-19")));

    assert(finance.addTransaction(
        Transaction(4, TransactionType::Expense, 200, "Utilities", "2026-11-19")));

    // Check duplicate transaction rejection
    assert(!finance.addTransaction(
        Transaction(1, TransactionType::Income, 100, "Sales", "2026-11-19")));

    // Check financial calculations
    assert(std::abs(finance.calculateIncome() - 2000) < 0.001);
    assert(std::abs(finance.calculateExpenses() - 800) < 0.001);
    assert(std::abs(finance.calculateNetProfit() - 1200) < 0.001);

    std::cout << "Income: " << finance.calculateIncome() << '\n';
    std::cout << "Expenses: " << finance.calculateExpenses() << '\n';
    std::cout << "Net Profit: " << finance.calculateNetProfit() << '\n';

    // Test CSV saving
    assert(finance.saveToCSV("finance_test.csv"));

    // Test CSV loading
    FinanceManager loadedFinance;
    assert(loadedFinance.loadFromCSV("finance_test.csv"));

    assert(loadedFinance.getTransactions().size() == 4);
    assert(std::abs(loadedFinance.calculateIncome() - 2000) < 0.001);
    assert(std::abs(loadedFinance.calculateExpenses() - 800) < 0.001);
    assert(std::abs(loadedFinance.calculateNetProfit() - 1200) < 0.001);

    std::cout << "\nFinance Manager tests passed successfully!\n";

    std::remove("finance_test.csv");

    return 0;
}
