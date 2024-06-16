# Calculator

Calculator is a command-line tool built using LLVM and C++ that parses and evaluates mathematical expressions, supporting basic arithmetic operations and advanced features. It leverages LLVM's powerful infrastructure for code generation and optimization, providing a robust platform for expression evaluation.

## Features

- **Expression Parsing:** Parses mathematical expressions into an abstract syntax tree (AST).
- **Arithmetic Operations:** Supports addition, subtraction, multiplication, and division.
- **Advanced Features:** Includes support for parentheses, unary operators, and floating-point numbers.
- **LLVM Integration:** Utilizes LLVM for code generation, optimization, and Just-In-Time (JIT) compilation.
- **Command-Line Interface:** Provides a simple command-line interface for entering and evaluating expressions.

## Requirements

- C++ compiler with C++20 support
- LLVM 12.0 or higher

## Installation

Clone the repository and build the project using CMake:

```bash
git clone https://github.com/your-username/calculator.git
cd calculator
mkdir build && cd build
cmake ..
cmake --build .
