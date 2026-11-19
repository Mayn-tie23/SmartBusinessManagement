
#include "FinanceWindow.h"
#include "FinanceManager.h"
#include "AllocationManager.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QGroupBox>
#include <QSet>

FinanceWindow::FinanceWindow(QWidget* parent) : QWidget(parent) {
    setWindowTitle("Financial Management");
    resize(600, 550);

    auto* main = new QVBoxLayout(this);
    auto* form = new QFormLayout();

    auto moneyInput = [this]() {
        auto* box = new QDoubleSpinBox(this);
        box->setRange(0, 1000000000);
        box->setDecimals(2);
        return box;
        };

    incomeInput = moneyInput();
    expensesInput = moneyInput();
    saleInput = moneyInput();

    form->addRow("Income:", incomeInput);
    form->addRow("Expenses:", expensesInput);
    form->addRow("Sale amount:", saleInput);

    methodInput = new QComboBox(this);
    methodInput->addItems({ "Per Sale", "Net Profit" });
    form->addRow("Allocation method:", methodInput);
    main->addLayout(form);

    profitLabel = new QLabel(this);
    main->addWidget(profitLabel);

    main->addWidget(new QLabel("Allocation Categories", this));
    categoryLayout = new QVBoxLayout();
    main->addLayout(categoryLayout);

    addCategoryButton = new QPushButton("Add Category", this);
    main->addWidget(addCategoryButton);

    auto* box = new QGroupBox("Percentage Summary", this);
    auto* boxLayout = new QVBoxLayout(box);
    percentageSummary = new QLabel(this);
    percentageSummary->setWordWrap(true);
    boxLayout->addWidget(percentageSummary);
    main->addWidget(box);

    calculateButton = new QPushButton("Calculate", this);
    resultLabel = new QLabel("Enter your financial details.", this);
    resultLabel->setWordWrap(true);

    main->addWidget(calculateButton);
    main->addWidget(resultLabel);
    main->addStretch();

    connect(addCategoryButton, &QPushButton::clicked,
        this, [this]() { addCategory(); });

    connect(calculateButton, &QPushButton::clicked,
        this, [this]() { calculate(); });

    connect(incomeInput, &QDoubleSpinBox::valueChanged,
        this, [this](double) { updateSummary(); });

    connect(expensesInput, &QDoubleSpinBox::valueChanged,
        this, [this](double) { updateSummary(); });

    addCategory();
}

void FinanceWindow::addCategory() {
    auto* row = new QWidget(this);
    auto* layout = new QHBoxLayout(row);

    auto* name = new QLineEdit(row);
    name->setPlaceholderText("Category");

    auto* percent = new QDoubleSpinBox(row);
    percent->setRange(0, 100);
    percent->setDecimals(2);
    percent->setSuffix("%");

    auto* remove = new QPushButton("Remove", row);

    layout->addWidget(name);
    layout->addWidget(percent);
    layout->addWidget(remove);
    categoryLayout->addWidget(row);

    connect(name, &QLineEdit::textChanged,
        this, [this]() { updateSummary(); });

    connect(percent, &QDoubleSpinBox::valueChanged,
        this, [this](double) { updateSummary(); });

    connect(remove, &QPushButton::clicked,
        this, [this, row]() {
            categoryLayout->removeWidget(row);
            row->deleteLater();
            updateSummary();
        });

    updateSummary();
}

void FinanceWindow::updateSummary() {
    double total = 0;
    QString details;

    for (int i = 0; i < categoryLayout->count(); ++i) {
        auto* row = categoryLayout->itemAt(i)->widget();
        if (!row) continue;

        auto* name = row->findChild<QLineEdit*>();
        auto* percent = row->findChild<QDoubleSpinBox*>();
        if (!name || !percent) continue;

        QString category = name->text().trimmed();
        if (category.isEmpty()) category = "Unnamed";

        total += percent->value();
        details += QString("%1: %2%\n")
            .arg(category)
            .arg(percent->value(), 0, 'f', 2);
    }

    details += QString("\nTotal: %1%").arg(total, 0, 'f', 2);

    if (total > 100.000001)
        details += QString(" | Exceeded by: %1%")
        .arg(total - 100, 0, 'f', 2);
    else
        details += QString(" | Remaining: %1%")
        .arg(100 - total, 0, 'f', 2);

    percentageSummary->setText(details);

    double profit = incomeInput->value() - expensesInput->value();

    if (profit > 0) {
        profitLabel->setText(QString("Net Profit: +%1")
            .arg(profit, 0, 'f', 2));
        profitLabel->setStyleSheet("color: green; font-weight: bold;");
    }
    else if (profit < 0) {
        profitLabel->setText(QString("Net Loss: -%1")
            .arg(-profit, 0, 'f', 2));
        profitLabel->setStyleSheet("color: red; font-weight: bold;");
    }
    else {
        profitLabel->setText("Break-even: 0.00");
        profitLabel->setStyleSheet("font-weight: bold;");
    }
}

void FinanceWindow::calculate() {
    FinanceManager finance;
    AllocationManager allocation;
    QSet<QString> names;

    double income = incomeInput->value();
    double expenses = expensesInput->value();
    double sale = saleInput->value();

    for (int i = 0; i < categoryLayout->count(); ++i) {
        auto* row = categoryLayout->itemAt(i)->widget();
        if (!row) continue;

        auto* name = row->findChild<QLineEdit*>();
        auto* percent = row->findChild<QDoubleSpinBox*>();
        if (!name || !percent) continue;

        QString category = name->text().trimmed();
        QString key = category.toLower();

        if (category.isEmpty() || names.contains(key)) {
            QMessageBox::warning(this, "Error",
                "Enter unique category names.");
            return;
        }

        names.insert(key);
        allocation.setPercentage(
            category.toStdString(), percent->value());
    }

    if (!allocation.validatePercentages()) {
        QMessageBox::warning(this, "Error",
            "Percentages must total 100%.");
        return;
    }

    double profit = finance.calculateNetProfit(income, expenses);
    AllocationMethod method = methodInput->currentIndex() == 0
        ? AllocationMethod::PerSale
        : AllocationMethod::NetProfit;

    auto amounts = allocation.allocateByMethod(
        sale, income, expenses, method);

    QString output = profit > 0
        ? QString("Net Profit: +%1\n").arg(profit, 0, 'f', 2)
        : profit < 0
        ? QString("Net Loss: -%1\n").arg(-profit, 0, 'f', 2)
        : QString("Break-even: 0.00\n");

    output += "\nAllocation Results:\n";

    for (const auto& item : amounts) {
        output += QString("%1: %2\n")
            .arg(QString::fromStdString(item.first))
            .arg(item.second, 0, 'f', 2);
    }

    if (amounts.empty())
        output += "No funds available for this allocation method.\n";

    resultLabel->setText(output);
}
