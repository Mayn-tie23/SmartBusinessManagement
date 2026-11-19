#pragma once

class FinanceManager {
public:
	double calculateNetProfit(double income, double expenses);
	bool isLoss(double income, double expenses);
};