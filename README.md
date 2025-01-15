# Minishell

Minishell is a simple, minimalistic shell program built to provide basic command-line interface functionalities. This project serves as an introduction to shell programming and system-level programming in a Unix-like environment.

## Features

- **Command Execution**: Executes binary commands located in the system's PATH.
- **Built-in Commands**: Includes essential commands like `cd`, `exit`, `echo`, etc.
- **Environment Variables**: Handles environment variables, including setting and retrieving them.
- **Pipes**: Supports piping between multiple commands (e.g., `ls | grep minishell`).
- **Redirections**: Implements input (`<`) and output (`>`/`>>`) redirections.
- **Signal Handling**: Handles signals like `Ctrl+C`, `Ctrl+D`, and `Ctrl+\` gracefully.
- **Error Handling**: Provides clear error messages for invalid commands or syntax errors.

## Getting Started

### Prerequisites

- A Unix-like operating system (Linux or macOS).
- GCC or a compatible C compiler.

### Installation

1. Clone the repository:
   ```bash
   git clone git@github.com:d2iv3r/minishell.git
   cd minishell
   ```
2. Compile the project:
   ```bash
   make
   ```

3. Run the shell:
   ```bash
   ./minishell
   ```

## Usage

Once the shell is running, you can enter commands just like in a standard shell. Here are some examples:

- Run a binary:
  ```bash
  ls -l
  ```
- Use a built-in command:
  ```bash
  cd /path/to/directory
  echo "Hello, Minishell!"
  exit
  ```
- Use pipes:
  ```bash
  cat file.txt | grep "keyword"
  ```
- Redirect input and output:
  ```bash
  ls > output.txt
  cat < input.txt
  ```

## Built-in Commands

| Command  | Description                                      |
|----------|--------------------------------------------------|
| `cd`     | Change the current directory.                   |
| `echo`   | Display a line of text.                         |
| `env`    | Display the current environment variables.       |
| `setenv` | Set or update an environment variable.           |
| `unsetenv` | Remove an environment variable.                |
| `exit`   | Exit the shell.                                 |


## Teammates

This project was developed collaboratively by:

- **Yahya Toumi**: [GitHub Profile](https://github.com/yahyatoumi)