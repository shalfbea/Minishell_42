HEADER := ./include/minishell.h

CC := clang

TestingFlags := -g3 #-fsanitize=address

READLINE_LIB := -I/Users/$(USER)/goinfre/.brew/Cellar/readline/8.1.2/include/ -L/Users/$(USER)/goinfre/.brew/Cellar/readline/8.1.2/lib/ -lreadline
FLAGS := -Wall -Wextra -Werror -I././include -I./libft/include -pthread  $(TestingFlags)

MINISHELL := minishell

PROMPTLIB := promptlib.a

LIBFT := ./libft/libft.a

SRC = main.c \
	  other/prompt.c other/signals.c other/ms_env.c \
	  debug/printers.c \
	  lexer/lexer.c lexer/lexer_wraps_lst.c lexer/lexer_free.c \
	  lexer/lexer_specials.c lexer/token_gluer.c \
	  parser/parser.c parser/command_lst.c \
	  parser/char_arrays.c parser/string_arrays.c \
	  env/env_check.c env/env_finder.c \
	  executor/executor.c executor/ft_init.c executor/open_pipes.c executor/lib_lst.c \
	  executor/run_commands.c executor/redirects.c executor/check_cmd.c \
      executor/get_next_line_utils.c executor/get_next_line.c executor/heredoc.c executor/heredoc02.c\
      executor/run_commands_utils.c \
	  builtins/builtins_utils.c builtins/builtins.c builtins/ft_export.c \
	  builtins/export_unset.c \
	  #builtins/exit.c

OBJ_DIR = ./obj/
SRC_DIR = ./src/

SRC_FILES = $(addprefix $(SRC_DIR), $(SRC))

OBJ_FILES = $(patsubst %.c, %.o, $(addprefix $(OBJ_DIR), $(SRC)))

RM := rm -rf

all: $(MINISHELL) #$(PROMPTLIB)

$(MINISHELL): $(LIBFT) $(HEADER) $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LIBFT) -o $(MINISHELL) $(READLINE_LIB) $(FLAGS)

$(LIBFT) :
	make -C ./libft

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR) :
	mkdir obj
	mkdir obj/lexer
	mkdir obj/parser
	mkdir obj/debug
	mkdir obj/env
	mkdir obj/builtins
	mkdir obj/other
	mkdir obj/executor

clean:
	$(RM) $(OBJ_DIR)
	make clean -C ./libft

fclean: clean
	$(RM) $(MINISHELL)
	make fclean -C ./libft

re: fclean all

norm: $(SRC_FILES)
	norminette $<

.PHONY: all clean fclean re norm bonus
