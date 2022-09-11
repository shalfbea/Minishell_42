# Minishell_42

As beautiful as shell

## About

This project is part of program in [School 21](https://21-school.ru/) ([Ecole 42](42.fr)).    
It's an mvp fork of bash.
The main goal of this project is to get deep inside of text parsing, process creation and syncronising using C.

## Requirements
- GNU GCC
- GNU Make
- readline lib installed

## Installation and usage

1. Download/Clone this repo
	> git clone https://github.com/shalfbea/Minishell_42
2. Get into the root directory of project and run make command
	> cd MINISHELL_42 ;
	> make
3. (Optional) Run make bonus to get some additional functionality
	> make bonus

3. To run program simply run ./minishell (or ./minishell_bonus)
	> ./minishell

## Technical task
The full task can be found here: [Minishell-subject](https://github.com/shalfbea/Minishell_42/blob/main/Minishell_subject.pdf)
### Quick summary:
- Only using c language is allowed
- Code-style should respect the [The Norm](https://github.com/MagicHatJo/-42-Norm/blob/master/norme.en.pdf)
- No memory leaks, segmentation faults, undefined behavior
- Implement some builtins: "echo", "cd", "pwd", "export", "unset", "env", "exit"
- Only allowed functions: readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, execve,
dup, dup2, pipe, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs
- Can also use [libft](https://github.com/shalfbea/libft) (own implementation of part of the library functions)
- Handle quotes, pipes, redicerets, $ just like bash do
- Handle signals
- Handle enviroment variables

### Bonus:
- Handle && and || with parenthesis for priorities.
- Wildcards * should work for the current working directory.

