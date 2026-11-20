
#include "FinanceManager.h"
#include "AllocationManager.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

bool equal(double a, double b) {
    return std::abs(a - b) < 0.000001;
}

int main() {
    FinanceManager finance;

    // Profit
    assert(equal(finance.calculateNetProfit(1000, 400), 600));

    // Loss
    assert(equal(finance.calculateNetProfit(200, 500), -300));
    assert(finance.isLoss(200, 500));

    // Break-even
    assert(equal(finance.calculateNetProfit(500, 500), 0));
    assert(!finance.isLoss(500, 500));

    AllocationManager allocation;

    // Invalid percentages
    assert(!allocation.setPercentage("Rent", 120));
    assert(!allocation.setPercentage("Rent", -10));
    assert(!allocation.setPercentage("", 20));

    // Valid percentages
    assert(allocation.setPercentage("Materials", 30));
    assert(allocation.setPercentage("Rent", 20));
    assert(allocation.setPercentage("Savings", 50));
    assert(allocation.validatePercentages());

    // Per-sale allocation
    auto sale = allocation.allocateByMethod(
        1000, 1000, 400, AllocationMethod::PerSale);

    assert(equal(sale.at("Materials"), 300));
    assert(equal(sale.at("Rent"), 200));
    assert(equal(sale.at("Savings"), 500));

    // Net-profit allocation
    auto profit = allocation.allocateByMethod(
        1000, 1000, 400, AllocationMethod::NetProfit);

    assert(equal(profit.at("Materials"), 180));
    assert(equal(profit.at("Rent"), 120));
    assert(equal(profit.at("Savings"), 300));

    // No allocation when operating at a loss
    auto loss = allocation.allocateByMethod(
        1000, 200, 500, AllocationMethod::NetProfit);

    assert(loss.empty());

    // No allocation at break-even
    auto zero = allocation.allocateByMethod(
        1000, 500, 500, AllocationMethod::NetProfit);

    assert(zero.empty());

    // Reject percentages that don't total 100%
    AllocationManager invalid;
    invalid.setPercentage("Materials", 30);
    invalid.setPercentage("Rent", 20);
    assert(!invalid.validatePercentages());

    // Reject negative allocation amounts
    bool rejected = false;

    try {
        allocation.allocate(-100);
    }
    catch (const std::invalid_argument&) {
        rejected = true;
    }

    assert(rejected);

    std::cout << "All finance unit tests passed!\n";
    return 0;
}
