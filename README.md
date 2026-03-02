# MINISHELL
*This project has been created as part of the 42 curriculum by rspinell & xiribar.*

## 📝 Description

**Minishell** is a minimalist shell replicating core Bash functionalities, focusing on process creation, file descriptors, and signal handling.

### 🚀 Features

* **Commands:** PATH-based, absolute, and relative execution.
* **Redirections & Pipes:** `<`, `>`, `>>`, `<<` (heredoc), and multi-stage pipelines (`|`).
* **Built-ins:** `echo -n`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.
* **Expansions & Signals:** `$VAR`, `$?`, and native behavior for `Ctrl-C`, `Ctrl-D`, `Ctrl-\`.

## 🛠 Technical Choices

We implemented a **Tokenizer → Expander → Parser → Executor** pipeline. Input is tokenized, expanded, and parsed. Execution relies on `pipe()`, `dup2()`, and `execve()` or the created builtins mentioned before. To ensure async-signal-safety, a single global `int` stores signal numbers without accessing main data structures.

## 💻 Instructions

### Compile
```bash
make
```

### Leak check:

Run after compilation: 
```bash
valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell
```

### Run tester:

Use the main-test.c file instead, just change its name temporarly. 
