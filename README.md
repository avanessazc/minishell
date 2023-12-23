# minishell
> Common core project at 42 School - Paris by: abesombe - ayzapata, students
>

## Introduction
This project is about creating a simple shell. Your own little bash.
You will learn a lot about processes and file descriptors

## General guidelines
Your shell should:
1. Display a prompt when waiting for a new command.
2. Have a working history.
3. Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
4. Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
5. Handle environment variables.
6. Your shell must implement the following builtins:
    - echo with option -n
    - cd with only a relative or absolute path
    - pwd with no options
    - export with no options
    - unset with no options
    - env with no options or arguments
    - exit with no options

<img width="562" alt="diagram" src="https://github.com/avanessazc/minishell/blob/main/minishell.png">
