*This project was created as part of the 42 curriculum by rspinell and xiribar.*

# Minishell

Minishell is a small Unix shell written in C. Its purpose is to reproduce a focused subset of Bash while learning how parsing, processes, signals and file descriptors interact inside a command interpreter.

## Features

- Interactive prompt and command history
- Executable resolution through PATH or relative/absolute paths
- Built-ins: echo, cd, pwd, export, unset, env and exit
- Input, output, append and heredoc redirections
- Multi-command pipelines
- Environment expansion for variables and the previous exit status
- Interactive signal handling

## Architecture

The shell is organized as a pipeline:

**Tokenizer → Expander → Parser → AST → Executor**

1. The tokenizer separates the input while preserving quoting rules.
2. The expander resolves environment variables and exit status.
3. The parser validates syntax and builds an Abstract Syntax Tree.
4. The executor traverses the structure, creates processes and configures pipes and redirections.
5. Built-ins run in the appropriate parent or child context depending on the command.

The implementation uses Unix primitives including fork, pipe, dup2, execve and waitpid.

## My work and learning

A major part of my work was reasoning about the boundary between parsing and execution: how commands, pipes and redirections should be represented recursively without making execution unnecessarily complex.

Breaking the problem into tokenization, expansion, parsing, AST construction and execution made it possible to test each stage independently. Comparing small command combinations against Bash helped isolate errors involving quoting, expansion, processes and file descriptors.

## Build and run

~~~bash
make
./minishell
~~~

For leak analysis:

~~~bash
valgrind --leak-check=full --show-leak-kinds=all \
  --suppressions=readline.supp ./minishell
~~~

## References and AI usage

The GNU Bash Reference Manual and standard Unix documentation were used to study expected behavior and system calls.

AI was used as a learning and debugging aid for discussing parser design, identifying possible edge cases and reviewing boilerplate. All submitted logic was reviewed, adapted to the 42 Norm and tested by the authors.
