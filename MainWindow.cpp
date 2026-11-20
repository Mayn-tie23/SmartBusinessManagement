#include "InventoryWindow.h"
#include "MainWindow.h"
#include "FinanceWindow.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {

    setWindowTitle("Smart Business Management");
    resize(800, 550);

    auto* page = new QWidget(this);
    auto* layout = new QVBoxLayout(page);
    auto* grid = new QGridLayout();

    auto* title = new QLabel("Smart Business Management", page);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size: 26px; font-weight: bold;");

    layout->addWidget(title);
    layout->addLayout(grid);

    inventoryButton = new QPushButton("Inventory", page);
    salesButton = new QPushButton("Sales", page);
    financeButton = new QPushButton("Finance", page);
    reportsButton = new QPushButton("Reports", page);

    grid->addWidget(inventoryButton, 0, 0);
    grid->addWidget(salesButton, 0, 1);
    grid->addWidget(financeButton, 1, 0);
    grid->addWidget(reportsButton, 1, 1);

    setCentralWidget(page);

    connect(inventoryButton, &QPushButton::clicked,
        this, [this]() { openInventory(); });

    connect(salesButton, &QPushButton::clicked,
        this, [this]() { openSales(); });

    connect(financeButton, &QPushButton::clicked,
        this, [this]() { openFinance(); });

    connect(reportsButton, &QPushButton::clicked,
        this, [this]() { openReports(); });
}

void MainWindow::openInventory() {
    auto* window = new InventoryWindow();
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();
}

void MainWindow::openSales() {
    QMessageBox::information(this, "Sales",
        "Sales interface is coming in Issue #11.");
}

void MainWindow::openFinance() {
    auto* window = new FinanceWindow();
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();
}

void MainWindow::openReports() {
    QMessageBox::information(this, "Reports",
        "Reports interface is coming in Issue #12.");
}
