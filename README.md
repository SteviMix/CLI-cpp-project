# CLI Interpreter (C++)

This project is an implementation of a command-line interface (CLI) interpreter developed in C++. It was realized as a project assignment for the Object-Oriented Programming course (2025/2026) at the School of Electrical Engineering (ETF), University of Belgrade.

## Project Overview
The interpreter acts as a shell that processes commands interactively or via batch files. It is designed to handle common operating system operations, file manipulation, and advanced command-line features such as I/O redirection and piping.

## Supported Commands
The interpreter supports the following commands:

* **`echo [argument]`**: Passes input characters to the output stream.
* **`prompt [argument]`**: Changes the command prompt symbol.
* **`time`**: Displays the current system real-time.
* **`date`**: Displays the current system date.
* **`touch [filename]`**: Creates an empty file.
* **`truncate [filename]`**: Clears the content of an existing file.
* **`rm [filename]`**: Deletes a file from the file system.
* **`wc -opt [argument]`**: Counts words (`-w`) or characters (`-c`) in the input.
* **`tr [argument] -what [with]`**: Translates/replaces character sequences.
* **`head -ncount [argument]`**: Outputs the first *n* lines of the input.
* **`batch [filename]`**: Executes a sequence of commands from a text file.

## Key Features
- **Object-Oriented Design**: Architecture focused on modularity, inheritance, and clean class abstractions.
- **I/O Redirection**: Supports `<` (input), `>` (output overwrite), and `>>` (output append).
- **Pipes**: Connects the output of one command to the input of another using the `|` operator.
- **Error Handling**: Comprehensive lexical and syntactic analysis with specific error messaging for unknown commands and semantic errors.

## Technical Stack
- **Language**: C++.
- **Concepts**: OOP techniques (encapsulation, abstraction, inheritance), stream manipulation (`iostream`, `fstream`), and modular memory management.

## Build and Execution
1. Clone the repository to your local machine.
2. Compile the project using your compiler (e.g., `g++` or `CMake`):
   ```bash
   mkdir build && cd build
   cmake ..
   make
3. Run the executable:
   ./cli_interpreter

Project developed for the Object-Oriented Programming course (2025/2026).
