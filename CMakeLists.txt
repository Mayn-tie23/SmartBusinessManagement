
cmake_minimum_required(VERSION 3.16)

project(SmartBusinessManagement LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt6 installation
list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.12.0/msvc2022_64")

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Graphs)

# ==========================================
# 1. Main Business Management Application
# ==========================================

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
    PRIVATE
    Qt6::Widgets
    Qt6::Graphs
)

# ==========================================
# 2. Qt Window Test
# ==========================================

add_executable(QtWindowTest
    QtWindowTest.cpp
 )

target_link_libraries(QtWindowTest
    PRIVATE Qt6::Widgets
)
# ==========================================
# 4. Financial Management GUI
# ==========================================

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

# ==========================================
# 5. Copy Required Qt DLLs
# ==========================================

foreach(target SmartBusinessManagement QtWindowTest FinanceGUI)

    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:${target}>
            $<TARGET_FILE_DIR:${target}>
        COMMAND_EXPAND_LISTS
    )

    # Copy Windows platform plugin
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:${target}>/platforms"

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/Qt/6.12.0/msvc2022_64/plugins/platforms/qwindowsd.dll"
            "$<TARGET_FILE_DIR:${target}>/platforms"
    )

endforeach()

# Automated finance unit tests
enable_testing()

add_executable(FinanceUnitTests
    FinanceUnitTests.cpp
    FinanceManager.cpp
    AllocationManager.cpp
)

target_compile_features(FinanceUnitTests PRIVATE cxx_std_17)

add_test(
    NAME FinanceUnitTests
    COMMAND FinanceUnitTests
)
