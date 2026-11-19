
#include "FinanceManager.h"

double FinanceManager::calculateNetProfit(
    double income, double expenses) {
    return income - expenses;
}

bool FinanceManager::isLoss(
    double income, double expenses) {
    return calculateNetProfit(income, expenses) < 0;
}
