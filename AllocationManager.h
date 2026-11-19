
#pragma once

#include <map>
#include <string>

enum class AllocationMethod {
    PerSale,
    NetProfit
};

class AllocationManager {
private:
    std::map<std::string, double> percentages;

public:
    bool setPercentage(const std::string& category,
        double percentage);

    bool validatePercentages() const;

    std::map<std::string, double> allocate(double amount) const;

    std::map<std::string, double> allocateByMethod(
        double saleAmount,
        double income,
        double expenses,
        AllocationMethod method) const;
};


