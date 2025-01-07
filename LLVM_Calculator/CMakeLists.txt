cmake_minimum_required(VERSION 3.14)

project(MyCalculatorProject VERSION 1.0 LANGUAGES CXX)

# Set C++17 standard
set(CMAKE_CXX_STANDARD 17)

# Find Qt libraries
find_package(Qt5 REQUIRED COMPONENTS Widgets)

# Find LLVM package
find_package(LLVM REQUIRED CONFIG)

# Include directories for LLVM
include_directories(${LLVM_INCLUDE_DIRS})

# Set the output directory for the project
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add the source files to the project
add_executable(MyCalculatorProject
    main.cpp
    calculator.cpp
    calculator.ui
    llvm_evaluator.cpp
    calculator.h
    llvm_evaluator.h
)

# Link the necessary Qt and LLVM libraries
target_link_libraries(MyCalculatorProject PRIVATE Qt5::Widgets LLVM::LLVM)
