# Simple Shell (# 0x16. C - Simple Shell) 🖥️

Welcome to the Simple Shell project! This repository contains a simple Unix shell implementation written in C. It provides basic functionality to execute commands and display a prompt for the user to interact with the shell.

## Table of Contents

-   [Description](#description)
-   [Tasks](#tasks)
    -   [0. Betty would be proud](#0-betty-would-be-proud)
    -   [1. Simple shell 0.1](#1-simple-shell-01)
    -   [2. Simple shell 0.2](#2-simple-shell-02)
    -   [3. Simple shell 0.3](#3-simple-shell-03)
    -   [4. Simple shell 0.4](#4-simple-shell-04)
    -   [5. Simple shell 1.0](#5-simple-shell-10)
    -   [6. Simple shell 0.1.1](#6-simple-shell-011)
    -   [7. Simple shell 0.2.1](#7-simple-shell-021)
    -   [8. Simple shell 0.4.1](#8-simple-shell-041)
    -   [9. setenv, unsetenv](#9-setenv-unsetenv)
    -   [10. cd](#10-cd)
    -   [11. ;](#11-)
    -   [12. && and ||](#12--and-)
    -   [13. alias](#13-alias)
    -   [14. Variables](#14-variables)
    -   [15. Comments](#15-comments)
    -   [16. File as input](#16-file-as-input)
-   [How to Run](#how-to-run)
-   [Dependencies](#dependencies)
-   [Author](#author)

## Description

This project implements a simple Unix shell that can execute commands, handle input and output redirection, and manage multiple built-in shell commands. It includes various functionalities such as executing commands, handling errors, and managing memory efficiently.

## Tasks

### 0. Betty would be proud

📝 **Task:** Write a beautiful code that passes the Betty checks.

### 1. Simple shell 0.1

🚀 **Task:** Write a UNIX command line interpreter.

### 2. Simple shell 0.2

🔧 **Task:** Handle command lines with arguments.

### 3. Simple shell 0.3

📄 **Task:** Handle the PATH. Fork must not be called if the command doesn’t exist.

### 4. Simple shell 0.4

🔍 **Task:** Implement the exit built-in, that exits the shell.

### 5. Simple shell 1.0

⚙️ **Task:** Implement the env built-in, that prints the current environment.

### 6. Simple shell 0.1.1

🐛 **Task:** Write your own getline function.

### 7. Simple shell 0.2.1

📥 **Task:** You are not allowed to use strtok.

### 8. Simple shell 0.4.1

🔄 **Task:** Handle arguments for the built-in exit.

### 9. setenv, unsetenv

🔧 **Task:** Implement the setenv and unsetenv builtin commands.

### 10. cd

🔄 **Task:** Implement the builtin command cd.

### 11. ;

📋 **Task:** Handle the commands separator `;`.

### 12. && and ||

🔗 **Task:** Handle the `&&` and `||` shell logical operators.

### 13. alias

🔤 **Task:** Implement the alias builtin command.

### 14. Variables

🔄 **Task:** Handle variables replacement. Handle the `$?` and `$$` variables.

### 15. Comments

💬 **Task:** Handle comments (`#`).

### 16. File as input

📄 **Task:** Your shell can take a file as a command line argument.

## How to Run

1.  **Clone the repository:**
    
    `git clone https://github.com/Linf0rd/simple_shell.git`
    
    `cd simple_shell` 
    
2.  **Compile the shell:**
    
    `gcc -Wall -Werror -Wextra -pedantic *.c -o hsh` 
    
3.  **Run the shell:**
    
    `./hsh` 
    

## Dependencies

-   **GCC:**  Ensure you have the GCC compiler installed. You can install it using:
        
    `sudo apt update`
    
    `sudo apt install build-essential` 
    

## Author

👨‍💻 **Linf0rd**