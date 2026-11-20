
#include "InventoryWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>

InventoryWindow::InventoryWindow(QWidget* parent)
    : QWidget(parent) {

    setWindowTitle("Inventory Management");
    resize(850, 550);

    auto* main = new QVBoxLayout(this);
    productTable = new QTableWidget(this);
    productTable->setColumnCount(4);
    productTable->setHorizontalHeaderLabels(
        { "ID", "Product", "Price", "Quantity" });
    productTable->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    productTable->setSelectionBehavior(
        QAbstractItemView::SelectRows);
    productTable->setEditTriggers(
        QAbstractItemView::NoEditTriggers);

    main->addWidget(productTable);

    auto* buttons = new QHBoxLayout();

    addButton = new QPushButton("Add Product", this);
    stockButton = new QPushButton("Update Stock", this);
    removeButton = new QPushButton("Remove Product", this);
    saveButton = new QPushButton("Save CSV", this);
    loadButton = new QPushButton("Load CSV", this);

    for (auto* button : { addButton, stockButton, removeButton,
                         saveButton, loadButton }) {
        buttons->addWidget(button);
    }

    main->addLayout(buttons);

    connect(addButton, &QPushButton::clicked,
        this, [this]() { addProduct(); });
    connect(stockButton, &QPushButton::clicked,
        this, [this]() { updateStock(); });
    connect(removeButton, &QPushButton::clicked,
        this, [this]() { removeProduct(); });
    connect(saveButton, &QPushButton::clicked,
        this, [this]() { saveInventory(); });
    connect(loadButton, &QPushButton::clicked,
        this, [this]() { loadInventory(); });

    refreshTable();
}

void InventoryWindow::refreshTable() {
    productTable->setRowCount(static_cast<int>(products.size()));

    for (int i = 0; i < static_cast<int>(products.size()); ++i) {
        const Product& p = products[i];

        productTable->setItem(i, 0,
            new QTableWidgetItem(QString::number(p.getId())));
        productTable->setItem(i, 1,
            new QTableWidgetItem(
                QString::fromStdString(p.getName())));
        productTable->setItem(i, 2,
            new QTableWidgetItem(
                QString::number(p.getPrice(), 'f', 2)));
        productTable->setItem(i, 3,
            new QTableWidgetItem(
                QString::number(p.getQuantity())));

        if (p.isLowStock()) {
            for (int col = 0; col < 4; ++col) {
                productTable->item(i, col)->setBackground(
                    QColor(255, 220, 220));
            }
        }
    }
}

void InventoryWindow::addProduct() {
    bool ok;
    int id = QInputDialog::getInt(
        this, "Product ID", "Enter ID:", 1, 1, 1000000, 1, &ok);
    if (!ok) return;

    for (const auto& product : products) {
        if (product.getId() == id) {
            QMessageBox::warning(this, "Duplicate ID",
                "This product ID already exists.");
            return;
        }
    }

    QString name = QInputDialog::getText(
        this, "Product Name", "Enter name:",
        QLineEdit::Normal, "", &ok);
    if (!ok) return;
    name = name.trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Invalid Name",
            "Product name cannot be empty.");
        return;
    }

    double price = QInputDialog::getDouble(
        this, "Product Price", "Enter price:",
        0, 0, 1000000000, 2, &ok);
    if (!ok) return;

    int quantity = QInputDialog::getInt(
        this, "Quantity", "Enter quantity:",
        0, 0, 1000000, 1, &ok);
    if (!ok) return;

    products.emplace_back(id, name.toStdString(), price, quantity);
    refreshTable();
}

void InventoryWindow::updateStock() {
    int row = productTable->currentRow();
    if (row < 0 || row >= static_cast<int>(products.size())) {
        QMessageBox::warning(this, "Selection",
            "Select a product first.");
        return;
    }

    bool ok;
    int change = QInputDialog::getInt(
        this, "Update Stock",
        "Enter stock change (negative to remove):",
        0, -1000000, 1000000, 1, &ok);
    if (!ok || change == 0) return;

    if (change > 0)
        products[row].addStock(change);
    else if (!products[row].removeStock(-change)) {
        QMessageBox::warning(this, "Insufficient Stock",
            "Not enough stock available.");
        return;
    }

    refreshTable();
}

void InventoryWindow::removeProduct() {
    int row = productTable->currentRow();
    if (row < 0 || row >= static_cast<int>(products.size())) {
        QMessageBox::warning(this, "Selection",
            "Select a product first.");
        return;
    }

    if (QMessageBox::question(
        this, "Remove Product", "Delete selected product?")
        != QMessageBox::Yes) {
        return;
    }

    products.erase(products.begin() + row);
    refreshTable();
}

void InventoryWindow::saveInventory() {
    saveInventoryToCSV(products, "inventory.csv");
    QMessageBox::information(this, "Saved",
        "Inventory saved to inventory.csv.");
}

void InventoryWindow::loadInventory() {
    try {
        products = loadInventoryFromCSV("inventory.csv");
        refreshTable();
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Load Error", e.what());
    }
}
