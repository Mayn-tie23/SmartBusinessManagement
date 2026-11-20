
cmake_minimum_required(VERSION 3.16)

project(SmartBusinessManagement LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

# Qt6 installation
list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.12.0/msvc2022_64")
find_package(Qt6 REQUIRED COMPONENTS Widgets Graphs)

# 1. Original business application - Thoko's main
add_executable(SmartBusinessManagement
    SmartBusinessManagement.cpp
    SmartBusinessManagement.h
    Product.h
    Product.cpp
    FinanceManager.h
    FinanceManager.cpp
    AllocationManager.h
    AllocationManager.cpp
)

target_link_libraries(SmartBusinessManagement
    PRIVATE Qt6::Widgets Qt6::Graphs
)

# 2. Qt window test
add_executable(QtWindowTest
    QtWindowTest.cpp
)

target_link_libraries(QtWindowTest
    PRIVATE Qt6::Widgets
)

# 3. Financial management GUI - Issue #7
add_executable(FinanceGUI
    FinanceGUI.cpp
    FinanceWindow.cpp
    FinanceWindow.h
    FinanceManager.cpp
    FinanceManager.h
    AllocationManager.cpp
    AllocationManager.h
)

target_link_libraries(FinanceGUI
    PRIVATE Qt6::Widgets
)

# 4. Automated finance unit tests
enable_testing()

add_executable(FinanceUnitTests
    FinanceUnitTests.cpp
    FinanceManager.cpp
    AllocationManager.cpp
)

add_test(
    NAME FinanceUnitTests
    COMMAND FinanceUnitTests
)

# 5. Main dashboard - Issue #9
add_executable(MainGUI
    MainGUI.cpp
    MainWindow.cpp
    MainWindow.h
    FinanceWindow.cpp
    FinanceWindow.h
    FinanceManager.cpp
    AllocationManager.cpp
)

target_link_libraries(MainGUI
    PRIVATE Qt6::Widgets
)

# 6. Copy Qt runtime files
foreach(target SmartBusinessManagement QtWindowTest FinanceGUI MainGUI)

    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:${target}>
            $<TARGET_FILE_DIR:${target}>
        COMMAND_EXPAND_LISTS
    )

    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:${target}>/platforms"

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/Qt/6.12.0/msvc2022_64/plugins/platforms/qwindowsd.dll"
            "$<TARGET_FILE_DIR:${target}>/platforms"
    )

endforeach()
