# CMakeList.txt : CMake project for SmartBusinessManagement, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SmartBusinessManagement")

list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.12.0/msvc2022_64")

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Graphs)


# Add source to this project's executable.
add_executable (SmartBusinessManagement "SmartBusinessManagement.cpp" 
"SmartBusinessManagement.h" "Product.h" "Product.cpp" "FinanceManager.cpp" "AllocationManager.h" "AllocationManager.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SmartBusinessManagement PROPERTY CXX_STANDARD 17)
endif()

# TODO: Add tests and install targets if needed.

target_link_libraries(SmartBusinessManagement
    PRIVATE
    Qt6::Widgets
    Qt6::Graphs
)

# Separate executable for testing the Qt window
add_executable(QtWindowTest QtWindowTest.cpp)

target_link_libraries(QtWindowTest
    PRIVATE Qt6::Widgets
)

# Copy Qt runtime DLLs beside the test executable
add_custom_command(TARGET QtWindowTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:QtWindowTest>
        $<TARGET_FILE_DIR:QtWindowTest>
    COMMAND_EXPAND_LISTS
)

# Copy the Qt Windows platform plugin
add_custom_command(TARGET QtWindowTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
        "$<TARGET_FILE_DIR:QtWindowTest>/platforms"

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Qt/6.12.0/msvc2022_64/plugins/platforms/qwindowsd.dll"
        "$<TARGET_FILE_DIR:QtWindowTest>/platforms"
)






