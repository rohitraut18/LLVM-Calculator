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

git clone https://github.com/your-username/calculator.git <br>
cd calculator<br>
mkdir build && cd build<br>
cmake ..<br>
cmake --build .<br>

## Usage
Run the calculator executable with a mathematical expression as an argument:

./calculator "2 * (3 + 4)"

This will evaluate the expression 2 * (3 + 4) and print the result.

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request for any enhancements, bug fixes, or new features.
