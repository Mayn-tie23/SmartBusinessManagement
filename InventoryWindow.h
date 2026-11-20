
#pragma once

#include <QWidget>
#include <vector>
#include "Product.h"

class QTableWidget;
class QPushButton;

class InventoryWindow : public QWidget {
public:
    explicit InventoryWindow(QWidget* parent = nullptr);

private:
    std::vector<Product> products;
    QTableWidget* productTable;
    QPushButton* addButton;
    QPushButton* stockButton;
    QPushButton* removeButton;
    QPushButton* saveButton;
    QPushButton* loadButton;

    void refreshTable();
    void addProduct();
    void updateStock();
    void removeProduct();
    void saveInventory();
    void loadInventory();
};

