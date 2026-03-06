*This project has been created as part of the 42 curriculum by rspinell, xiribar.*

# Minishell: As beautiful as a shell

## 📝 Description

**Minishell** is a minimalist shell replicating the core functionalities of Bash. The primary goal of this project is to gain extensive knowledge about processes and file descriptors by building a small command-line interpreter.

### 🚀 Features

* **Prompt & History:** Displays a prompt when waiting for a new command and maintains a working command history.
* **Execution:** Searches and launches the right executable based on the `PATH` variable or using a relative or absolute path.
* **Built-ins:**
* `echo` with option `-n`
* `cd` with only a relative or absolute path
* `pwd` with no options
* `export` with no options
* `unset` with no options
* `env` with no options or arguments
* `exit` with no options


* **Redirections:**
* `<` redirects input.
* `>` redirects output.
* `<<` (heredoc) reads input until a delimiter is seen.
* `>>` redirects output in append mode.


* **Pipes:** Implements pipes (`|` character) where the output of each command is connected to the input of the next.
* **Environment Variables:** Handles expansion of `$VAR` and `$?` (exit status).
* **Signals:** Native behavior for `Ctrl-C` (new prompt), `Ctrl-D` (exit), and `Ctrl-\` (nothing).

## 🛠 Technical Choices

We implemented a **Tokenizer → Expander → Parser → Executor** pipeline. Input is tokenized, expanded, and then parsed into an Abstract Syntax Tree (AST). Execution relies on system calls such as `pipe()`, `dup2()`, and `execve()`. To ensure async-signal-safety and comply with project requirements, a single global `int` stores signal numbers without accessing main data structures.

## 💻 Instructions

### Compilation

To compile the project, run:

```bash
make

```

### Execution

Run the executable after compilation:

```bash
./minishell

```

### Leak Check

Use Valgrind with the provided suppression file to check for memory leaks (ignoring known `readline` leaks):

```bash
valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

```

## 📚 Resources

**Classic References:**

* [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/) for expected shell behavior.
* Standard C library documentation for process management (`fork`, `waitpid`, `execve`) and file descriptors (`pipe`, `dup2`).

**AI Usage:**
AI was used in this project to assist with the following tasks:

* **Parser Design:** Discussing the logic for the Abstract Syntax Tree (AST) structure and pipeline execution.
* **Debugging:** Identifying potential edge cases in quote handling and variable expansion.
* **Boilerplate:** Assisting with the initial structure of utility functions and the Makefile.
* *Note: All AI-generated logic was manually reviewed, refactored to comply with the Norm, and thoroughly tested by the authors.*