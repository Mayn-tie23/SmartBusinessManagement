
# Smart Business Management System
## Class Interfaces

## 1. Overview

This document defines the proposed C++17 interfaces for the Inventory, Sales, Finance, Analytics, Storage and GUI modules.

## 2. Inventory Module

### Product.h

Stores product information and manages stock.

```cpp
class Product {
private:
    int id;
    std::string name;
    double price;
    int quantity;

public:
    Product(int id, std::string name, double price, int quantity);
    int getId() const;
    std::string getName() const;
    double getPrice() const;
    int getQuantity() const;
    void addStock(int amount);
    bool removeStock(int amount);
    bool isLowStock() const;
};

void saveInventoryToCSV(
    const std::vector<Product>& inventory,
    const std::string& filename);

std::vector<Product> loadInventoryFromCSV(
    const std::string& filename);
```

### InventoryManager.h

Manages products and inventory records.

```cpp
class InventoryManager {
private:
    std::vector<Product> products;

public:
    bool addProduct(const Product& product);
    bool removeProduct(int id);
    bool updateStock(int id, int quantity);
    Product* findProduct(int id);
    const std::vector<Product>& getProducts() const;
    bool saveToCSV(const std::string& filename) const;
    bool loadFromCSV(const std::string& filename);
};
```

## 3. Sales Module

### Sale.h

Represents a sales transaction.

```cpp
class Sale {
private:
    int saleId, productId, quantity;
    double unitPrice;
    std::string date;

public:
    Sale(int saleId, int productId, int quantity,
         double unitPrice, std::string date);
    int getSaleId() const;
    int getProductId() const;
    int getQuantity() const;
    double getUnitPrice() const;
    std::string getDate() const;
    double getTotal() const;
};
```

### SalesManager.h

Records sales and updates stock.

```cpp
class SalesManager {
private:
    std::vector<Sale> sales;
    InventoryManager& inventory;

public:
    explicit SalesManager(InventoryManager& inventory);
    bool recordSale(const Sale& sale);
    double calculateRevenue() const;
    const std::vector<Sale>& getSales() const;
    bool saveToCSV(const std::string& filename) const;
    bool loadFromCSV(const std::string& filename);
};
```

## 4. Finance Module

### Transaction.h

Stores income and expense records.

```cpp
enum class TransactionType { Income, Expense };

class Transaction {
private:
    int id;
    TransactionType type;
    double amount;
    std::string category, date;

public:
    Transaction(int id, TransactionType type,
                double amount, std::string category,
                std::string date);
    int getId() const;
    TransactionType getType() const;
    double getAmount() const;
    std::string getCategory() const;
    std::string getDate() const;
};
```

### FinanceManager.h

Calculates income, expenses and profit or loss.

```cpp
class FinanceManager {
private:
    std::vector<Transaction> transactions;

public:
    bool addTransaction(const Transaction& transaction);
    double calculateIncome() const;
    double calculateExpenses() const;
    double calculateNetProfit() const;
    const std::vector<Transaction>& getTransactions() const;
    bool saveToCSV(const std::string& filename) const;
    bool loadFromCSV(const std::string& filename);
};
```

### AllocationManager.h

Distributes available funds using user percentages.

```cpp
class AllocationManager {
private:
    std::map<std::string, double> percentages;

public:
    bool setPercentage(const std::string& category,
                       double percentage);
    bool validatePercentages() const;
    std::map<std::string, double> allocate(double amount) const;
    const std::map<std::string, double>&
        getPercentages() const;
};
```

## 5. Analytics Module

### PerformanceAnalyzer.h

Analyzes growth, decline and stability.

```cpp
enum class PerformanceStatus { Growth, Decline, Stable };

class PerformanceAnalyzer {
public:
    double calculatePercentageChange(
        double previous, double current) const;
    PerformanceStatus analyze(
        double previous, double current) const;
    std::vector<double> calculateTrend(
        const std::vector<double>& values) const;
};
```

## 6. CSV Storage Module

### CSVStorage.h

Provides shared CSV reading and writing functions.

```cpp
class CSVStorage {
public:
    static bool writeRows(
        const std::string& filename,
        const std::vector<std::vector<std::string>>& rows);

    static std::vector<std::vector<std::string>>
        readRows(const std::string& filename);
};
```

## 7. GUI Module

Qt6 provides the graphical interface.

```cpp
// MainWindow.h
class MainWindow : public QMainWindow {
public:
    explicit MainWindow(QWidget* parent = nullptr);
    void showInventory();
    void showSales();
    void showFinance();
    void showReports();
};

// InventoryWindow.h
class InventoryWindow : public QWidget {
private:
    InventoryManager& inventory;
public:
    explicit InventoryWindow(
        InventoryManager& inventory, QWidget* parent = nullptr);
    void refreshProducts();
};

// SalesWindow.h
class SalesWindow : public QWidget {
private:
    SalesManager& sales;
public:
    explicit SalesWindow(
        SalesManager& sales, QWidget* parent = nullptr);
    void refreshSales();
};

// FinanceWindow.h
class FinanceWindow : public QWidget {
private:
    FinanceManager& finance;
public:
    explicit FinanceWindow(
        FinanceManager& finance, QWidget* parent = nullptr);
    void refreshFinances();
};

// ReportsWindow.h
class ReportsWindow : public QWidget {
public:
    explicit ReportsWindow(QWidget* parent = nullptr);
    void displayRevenueGraph(const std::vector<double>& values);
    void displayProfitGraph(const std::vector<double>& values);
};
```

## 8. Module Dependencies

| Module | Depends On |
|--------|------------|
| Inventory | Product, CSV |
| Sales | Sale, Inventory |
| Finance | Transaction, Sales |
| Allocation | Financial values |
| Analytics | Sales, Finance |
| GUI | Business modules |

## 9. Integration and Testing

- Use C++17 and follow agreed interfaces.
- Keep business logic separate from the GUI.
- Validate stock, sales and financial calculations.
- Prevent duplicate transactions and double-counted revenue.
- Ensure allocation percentages total 100%.
- Test CSV loading, saving and error handling.
- Test growth, decline and stability calculations.
- Use GitHub branches and Pull Requests.
