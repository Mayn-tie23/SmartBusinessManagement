
#pragma once
#include <QWidget>

class QDoubleSpinBox;
class QComboBox;
class QVBoxLayout;
class QPushButton;
class QLabel;

class FinanceWindow : public QWidget {
public:
    explicit FinanceWindow(QWidget* parent = nullptr);

private:
    QDoubleSpinBox* incomeInput;
    QDoubleSpinBox* expensesInput;
    QDoubleSpinBox* saleInput;
    QComboBox* methodInput;
    QVBoxLayout* categoryLayout;
    QPushButton* addCategoryButton;
    QPushButton* calculateButton;
    QLabel* resultLabel;
    QLabel* percentageSummary;
    QLabel* profitLabel;

    void addCategory();
    void updateSummary();
    void calculate();
};
