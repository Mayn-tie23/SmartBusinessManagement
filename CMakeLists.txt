
cmake_minimum_required(VERSION 3.8)

project(SmartBusinessManagement)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main application
add_executable(SmartBusinessManagement
    SmartBusinessManagement.cpp
    Product.cpp
    Sale.cpp
    InventoryManager.cpp
    SalesManager.cpp
    CSVStorage.cpp
    Transaction.cpp
    FinanceManager.cpp
)

# Enable testing
include(CTest)

if(BUILD_TESTING)

    # Sale tests
    add_executable(SaleTest
        Sale.cpp
        SaleTest.cpp
    )
    add_test(NAME SaleTest COMMAND SaleTest)

    # Inventory tests
    add_executable(InventoryManagerTest
        Product.cpp
        InventoryManager.cpp
        InventoryManagerTest.cpp
    )
    add_test(NAME InventoryManagerTest COMMAND InventoryManagerTest)

    # Sales and inventory integration tests
    add_executable(SalesInventoryTest
        Product.cpp
        Sale.cpp
        InventoryManager.cpp
        SalesManager.cpp
        CSVStorage.cpp
        SalesInventoryTest.cpp
    )
    add_test(NAME SalesInventoryTest COMMAND SalesInventoryTest)

    # CSV storage tests
    add_executable(CSVStorageTest
        CSVStorage.cpp
        CSVStorageTest.cpp
    )
    add_test(NAME CSVStorageTest COMMAND CSVStorageTest)

    # Sales CSV tests
    add_executable(SalesManagerCSVTest
        Product.cpp
        Sale.cpp
        InventoryManager.cpp
        SalesManager.cpp
        CSVStorage.cpp
        SalesManagerCSVTest.cpp
    )
    add_test(NAME SalesManagerCSVTest COMMAND SalesManagerCSVTest)
    # Finance manager tests
    add_executable(FinanceManagerTest
        Transaction.cpp
        FinanceManager.cpp
        CSVStorage.cpp
        FinanceManagerTest.cpp
    )
    add_test(NAME FinanceManagerTest COMMAND FinanceManagerTest)
endif()
