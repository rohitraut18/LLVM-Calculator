# Calculator

Calculator is a command-line tool built using LLVM and C++ that parses and evaluates mathematical expressions, supporting basic arithmetic operations and advanced features. It leverages LLVM's powerful infrastructure for code generation and optimization, providing a robust platform for expression evaluation. Additionally, it has a graphical user interface (GUI) powered by Qt, enabling a user-friendly interaction with the calculator.

## Features

- **Expression Parsing:** Parses mathematical expressions into an abstract syntax tree (AST).
- **Arithmetic Operations:** Supports addition, subtraction, multiplication, and division.
- **Advanced Features:** Includes support for parentheses, unary operators, and floating-point numbers.
- **LLVM Integration:** Utilizes LLVM for code generation, optimization, and Just-In-Time (JIT) compilation.
- **Command-Line Interface (CLI):** Provides a simple command-line interface for entering and evaluating expressions.
- **Qt GUI:** A simple graphical interface built with Qt that allows users to enter mathematical expressions and view results interactively.

## Requirements

- C++ compiler with C++20 support
- LLVM 12.0 or higher
- Qt 5 or higher (for GUI functionality)

## Installation

Clone the repository and build the project using CMake:

```bash
git clone https://github.com/your-username/calculator.git
cd calculator
mkdir build && cd build
cmake ..
cmake --build .

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request for any enhancements, bug fixes, or new features.
