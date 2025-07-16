
# Simple Shell (# 0x16. C - Simple Shell) 🖥️

Welcome to the Simple Shell project! This repository contains a simple Unix shell implementation written in C. It provides basic functionality to execute commands and display a prompt for the user to interact with the shell.

## Features

- Command execution with arguments
- Built-in commands: `exit`, `env`, `setenv`, `unsetenv`, `cd`, `alias`
- Command chaining with `;`, logical operators `&&` and `||`
- Comments (`#`) are ignored
- Variable replacement: `$VAR`, `${VAR}`, `$?`, `$$`
- Alias support
- Customizable prompt via `PROMPT` and `PROMPT_COLOR` environment variables
- Background job support with `&`
- Robust error handling and resource management

## How to Run

1. **Clone the repository:**
    ```sh
    git clone https://github.com/Linf0rd/simple_shell.git
    cd simple_shell
    ```
2. **Compile the shell:**
    ```sh
    gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
    ```
3. **Run the shell:**
    ```sh
    ./hsh
    ```

## Customization

- Set a custom prompt:
    ```sh
    export PROMPT="mysh> "
    ```
- Set a prompt color (ANSI, e.g. red):
    ```sh
    export PROMPT_COLOR="\033[1;31m"
    ```

## Background Jobs

- Run a command in the background:
    ```sh
    sleep 10 &
    ```

## Author

👨‍💻 **Linf0rd**