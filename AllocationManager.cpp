
#include "AllocationManager.h"
#include <cmath>
#include <stdexcept>

bool AllocationManager::setPercentage(
    const std::string& category, double percentage) {

    if (category.empty() || !std::isfinite(percentage) ||
        percentage < 0 || percentage > 100) {
        return false;
    }

    percentages[category] = percentage;
    return true;
}

bool AllocationManager::validatePercentages() const {
    if (percentages.empty()) return false;

    double total = 0;

    for (const auto& entry : percentages) {
        total += entry.second;
    }

    return std::abs(total - 100.0) < 0.000001;
}

std::map<std::string, double>
AllocationManager::allocate(double amount) const {

    if (!std::isfinite(amount) || amount < 0 ||
        !validatePercentages()) {
        throw std::invalid_argument("Invalid allocation");
    }

    std::map<std::string, double> result;

    for (const auto& entry : percentages) {
        result[entry.first] = amount * entry.second / 100.0;
    }

    return result;
}

std::map<std::string, double>
AllocationManager::allocateByMethod(
    double saleAmount,
    double income,
    double expenses,
    AllocationMethod method) const {

    if (method == AllocationMethod::PerSale) {
        return allocate(saleAmount);
    }

    if (method == AllocationMethod::NetProfit) {
        double profit = income - expenses;

        if (profit <= 0) {
            return {};
        }

        return allocate(profit);
    }

    return {};
}
