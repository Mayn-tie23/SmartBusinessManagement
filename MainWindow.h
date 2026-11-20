
#pragma once

#include <QMainWindow>

class QPushButton;

class MainWindow : public QMainWindow {
public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    QPushButton* inventoryButton;
    QPushButton* salesButton;
    QPushButton* financeButton;
    QPushButton* reportsButton;

    void openInventory();
    void openSales();
    void openFinance();
    void openReports();
};

