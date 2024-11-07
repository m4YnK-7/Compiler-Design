# Compiler Design

Welcome to the **Compiler Design Implementation** repository! This collection of projects explores the fundamental concepts of lexical/semantic/syntax analysis,compiler construction, code generation, optimization, and parallel processing. Each module is designed to provide hands-on experience with essential compiler components, from lexical analysis to intermediate code generation, and optimizations to parallel computing techniques.

## Overview

This repository is structured to simulate the stages of compilation, illustrating how code is processed, transformed, and optimized. Each module focuses on a specific aspect of compiler design or parallel computing, and the projects are implemented in C for performance and low-level control.This project serves as a learning resource, providing practical examples and modular code that illustrate each stage of the compilation process.


## Project Modules

### 1. Lexical Analyzer
The lexical analyzer is the first phase in the compilation process, responsible for breaking down input code into tokens that represent keywords, operators, identifiers, and other elements.

- **Tokenization**: Identifies and classifies keywords, operators, identifiers, and literals.
- **Symbol Table**: Creates and manages a symbol table to store variables, function names, and other identifiers.
- **RE to DFA**: Converts regular expressions into a Deterministic Finite Automaton (DFA) for efficient pattern matching.

### 2. Syntax Analyzer
The syntax analyzer, or parser, constructs parse trees based on grammar rules to ensure the input code's syntactic correctness.

- **Parse Tree Construction**: Builds parse trees and validates code syntax using predefined grammar rules.
- **Grammar Transformation**: Eliminates left factoring and left recursion in the grammar to simplify parsing.
- **Parser Implementations**: Implements commonly used parsers, such as LL(1), SLR, and LALR parsers.

### 3. Semantic Analyzer
The semantic analyzer checks for semantic consistency in the code, linking syntax to meaning with translation schemes.

- **Syntax-Directed Definitions**: Applies syntax-directed definitions for associating semantic actions with grammar rules.
- **Translation Schemes**: Implements translation schemes, including L-attributed syntax for managing evaluation order.
- **Arithmetic Translator**: Constructs a syntax-directed translator for simple arithmetic expressions.

### 4. Intermediate Code Generation
Intermediate code generation transforms high-level source code into an intermediate form, bridging the gap between source code and machine code.

- **Three-Address Code**: Generates three-address code for expressions and control flow statements.
- **Syntax Tree and Back Patching**: Converts syntax trees to intermediate code and uses back patching for jump statements.
- **Switch Case Representation**: Implements intermediate code for switch-case structures.

### 5. Code Optimization
Code optimization improves the efficiency of the intermediate code without altering program functionality.

- **Optimization Principles**: Demonstrates common sources of optimization for improving code performance.
- **Peephole Optimization**: Uses peephole optimization techniques to refine and simplify intermediate code.
- **Virtual Machine Code Generator**: Implements a naïve code generator for a virtual machine, showcasing machine-independent optimizations.

### 6. Code Generation
The code generation phase produces final code, preparing it for execution on a specific machine.

- **Basic Code Generation**: Implements register allocation and next-use analysis for efficient resource management.
- **Activation Record Simulation**: Simulates stack frames and activation records for handling function calls and recursion.
- **Runtime Simulation**: Generates intermediate code and simulates a runtime environment.

### 7. Parallelism
The parallelism module explores concepts in parallel computing to enhance performance and efficiency in computational tasks.

- **Parallel Array Processing**: Implements parallel processing using Pthreads and vectorization for optimized array operations.
- **Cache-Optimized Matrix Multiplication**: Applies cache optimization techniques and parallel processing for efficient matrix multiplication.
- **DSL Interpreter with Instruction Scheduling**: Develops a basic DSL interpreter with instruction scheduling to simulate software pipelining.

## Purpose
This project is intended for educational purposes, particularly for students and enthusiasts learning about compiler construction. By understanding the flow of a compiler, you will gain insights into how programming languages are processed, compiled, and translated into executable code.

## Getting Started

### Prerequisites
To run these projects, you need:
- **C Compiler** (GCC or Clang recommended)
- **Make** (for building projects, if Makefiles are included)
- **POSIX Threads Library** (for parallelism projects)

## Installation
1. Clone the repository to your local machine:
    ```bash
    git clone https://github.com/m4YnK-7/Compiler-Design.git
    ```
2. Navigate to the project directory:
    ```bash
    cd Compiler-Design
    ```

3. Follow the setup instructions for any dependencies if needed.

## Contributing
Contributions are welcome! If you’d like to add new features, fix bugs, or improve documentation, please fork the repository and open a pull request.

1. Fork the repository
2. Create a new branch (`git checkout -b feature-branch`)
3. Commit your changes (`git commit -am 'Add new feature'`)
4. Push to the branch (`git push origin feature-branch`)
5. Open a pull request

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments
- Compiler construction and parallelism concepts were explored as part of learning and practice.
- Special thanks to the open-source community and academic resources for guidance.
