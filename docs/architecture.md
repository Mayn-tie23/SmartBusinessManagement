
# Smart Business Management System
## System Architecture

## 1. Overview

The Smart Business Management System is a C++ application for managing inventory, sales and financial operations.

It uses OOP, Qt for the GUI and CSV files for data storage.

## 2. System Modules


| Module | Responsibility | Owner |
|--------|----------------|-------|
| Inventory | Products and stock management | A & B |
| Sales | Sales logic and revenue calculation | B |
| Finance | Profit, loss and financial allocation | A & B |
| Analytics | Business performance graphs | A |
| GUI | Main menu, inventory, sales and finance screens | A |
| Storage | CSV saving and loading | B |
| Setup | Qt6 installation and CMake configuration | A |


## 3. Module Dependencies

| Module | Depends On |
|--------|------------|
| Inventory | Storage |
| Sales | Inventory, Storage |
| Finance | Sales, Storage |
| Allocation | Finance |
| Analytics | Sales, Finance |
| GUI | All modules |

### Module Flow

Inventory → Sales → Finance → Analytics

Allocation uses financial results to distribute funds.

## 4. Class Hierarchy and OOP

### Class Structure

```text
Product
  |-- PhysicalProduct
  |-- MaterialProduct

InventoryManager
  |-- Manages Products

SalesManager
  |-- Manages Sales
  |-- Uses InventoryManager

FinanceManager
  |-- Manages Transactions
  |-- Uses AllocationManager

PerformanceAnalyzer
  |-- Analyzes financial performance
```

### OOP Concepts

| Concept | Application |
|---------|-------------|
| Encapsulation | Private attributes |
| Abstraction | Public methods |
| Inheritance | Product subclasses |
| Polymorphism | Virtual product methods |
| Composition | Manager classes |
| STL | Vectors and maps |


## 5. Design Patterns

| Pattern | Implementation | Purpose |
|---------|----------------|---------|
| Factory | ProductFactory | Creates different product types |
| Strategy | AllocationManager | Supports different allocation methods |
| Observer | Inventory and GUI | Updates the stock display |
| MVC | GUI and business modules | Separates interface from logic |

## 6. STL Usage and Templates

### STL Usage

| STL Feature | Where Used | Purpose |
|-------------|------------|---------|
| std::vector | Inventory, Sales | Store products and sales |
| std::map | AllocationManager | Store allocation percentages |
| std::string | All modules | Store names and descriptions |
| std::algorithm | Inventory, Analytics | Search and sort records |
| std::fstream | Storage | Read and write CSV files |

### Templates

| Template | Purpose |
|----------|---------|
| Repository<T> | Generic data storage interface |
| Report<T> | Generate reports for different data types |

## 7. CSV Data Storage

| File | Contents |
|------|----------|
| products.csv | Product ID, name, price, quantity |
| sales.csv | Sale ID, date, product, quantity, total |
| finances.csv | Income, expenses and categories |
| allocations.csv | Allocation categories and percentages |

CSV files provide persistent storage without requiring a database.

## 8. Data Flow

1. User enters information through the GUI.
2. InventoryManager manages products and stock.
3. SalesManager records sales and reduces stock.
4. FinanceManager calculates income, expenses and profit or loss.
5. AllocationManager distributes available funds.
6. PerformanceAnalyzer evaluates growth, decline or stability.
7. Updated records are saved to CSV files.


## 9. Integration Points

| Stage | Task | Members |
|-------|------|---------|
| 1 | Agree on class interfaces | A & B |
| 2 | Complete Product and Inventory | A & B |
| 3 | Connect Sales to Inventory | A & B |
| 4 | Integrate Finance and Allocation | A & B |
| 5 | Connect GUI and Analytics | A & B |
| 6 | Final testing and documentation | A & B |

Modules will be integrated gradually to detect errors early.

## 10. File Structure

```text
SmartBusinessManagement/
├── src/
│   ├── inventory/
│   ├── sales/
│   ├── finance/
│   ├── analytics/
│   └── gui/
├── data/
│   ├── products.csv
│   ├── sales.csv
│   ├── finances.csv
│   └── allocations.csv
├── tests/
├── docs/
├── CMakeLists.txt
└── README.md
```

The structure is planned and will be created as development progresses.

## 11. Build System

| Technology | Purpose |
|------------|---------|
| C++17 | Main programming language |
| Visual Studio 2022 | Development environment |
| CMake | Project build system |
| Qt6 | Graphical user interface |
| CSV | Data storage |
| GitHub | Version control |
| Google Test | Unit testing |

## 12. Testing Strategy

| Module | Tests |
|--------|-------|
| Inventory | Product creation, stock updates |
| Sales | Revenue calculation, transaction recording |
| Finance | Profit, loss and expense calculations |
| Allocation | Percentage validation and fund distribution |
| Analytics | Growth, decline and stability detection |
| Storage | CSV saving and loading |
| GUI | Navigation and input validation |

Both members will test their modules before final integration.


## 13. Team Responsibilities

### Member A - Mayn-tie23

| Issue | Task |
|-------|------|
| #7 | Financial Profit & Percentage Allocation |
| #8 | Qt6 Installation & CMake Setup |
| #9 | Design Main Menu & Navigation |
| #10 | Build Inventory UI |
| #11 | Build Sales & Financial UI |
| #12 | Data Visualization Graphs |

### Member B - thokoeve2-cpu

| Issue | Task |
|-------|------|
| #2 | Sales Logic & Revenue Calculation |
| #3 | Financial Allocation Logic |
| #4 | CSV Saving & Loading |
| #5 | Create Sale Class |
| #6 | Connect Sales to Inventory |

Both members will contribute to testing, debugging, documentation and final integration.
