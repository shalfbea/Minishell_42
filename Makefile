HEADER := ./include/minishell.h

CC := clang

TestingFlags := -g3 #-fsanitize=address

#READLINE_LIB := -I/Users/$(USER)/goinfre/.brew/Cellar/readline/8.1.2/include/ -L/Users/$(USER)/goinfre/.brew/Cellar/readline/8.1.2/lib/ -lreadline
READLINE_LIB := -lreadline
FLAGS := -Wall -Wextra -Werror -I././include -I./libft/include -pthread $(TestingFlags)
BONUS_FLAGS := -D ENABLE_BONUS=1
MINISHELL := minishell
MINISHELL_BONUS := minishell_bonus
PROMPTLIB := promptlib.a

LIBFT := ./libft/libft.a

SRC = main.c \
	  other/prompt.c other/signals.c other/ms_env.c \
	  lexer/lexer.c lexer/lexer_wraps_lst.c lexer/lexer_free.c \
	  lexer/lexer_specials.c lexer/token_gluer.c \
	  parser/parser.c parser/command_lst.c \
	  parser/char_arrays.c parser/string_arrays.c \
	  parser/parser_utils.c \
	  env/env_check.c env/env_finder.c \
	  executor/executor.c executor/ft_init.c executor/open_pipes.c executor/lib_lst.c \
	  executor/run_commands.c executor/redirects.c executor/check_cmd.c \
      executor/get_next_line_utils.c executor/get_next_line.c executor/heredoc.c executor/heredoc02.c \
      executor/run_commands_utils.c executor/heredoc_utils.c executor/put_error.c\
	  builtins/builtins_utils.c builtins/builtins.c builtins/ft_export.c \
	  builtins/ft_unset.c builtins/builtins_02.c builtins/retrieve_fd.c \
	  builtins/export_add_functions.c builtins/export_working_with_names.c\
	  lexer/wildcards.c \
	  debug/commands_printer.c debug/env_printer.c debug/groups_printer.c debug/lexer_printer.c

SRC_BONUS = bonus/logical.c bonus/stack_operations.c bonus/groups.c bonus/groups_execution.c

OBJ_DIR = ./obj/
SRC_DIR = ./src/

SRC_FILES = $(addprefix $(SRC_DIR), $(SRC))
SRC_FILES_BONUS = $(addprefix $(SRC_DIR), $(SRC_BONUS))
OBJ_FILES = $(patsubst %.c, %.o, $(addprefix $(OBJ_DIR), $(SRC)))
OBJ_FILES_BONUS = $(patsubst %.c, %.o, $(addprefix $(OBJ_DIR), $(SRC_BONUS)))

RM := rm -rf

all: $(MINISHELL) #$(PROMPTLIB)

$(MINISHELL): $(LIBFT) $(HEADER) $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LIBFT) -o $(MINISHELL) $(READLINE_LIB) $(FLAGS)

$(MINISHELL_BONUS): $(LIBFT) $(HEADER) $(OBJ_FILES) $(OBJ_FILES_BONUS)
	$(CC) $(OBJ_FILES) $(OBJ_FILES_BONUS) $(LIBFT) -o $(MINISHELL) $(READLINE_LIB) $(FLAGS) $(BONUS_FLAGS)

$(LIBFT) :
	make -C ./libft

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

obj: $(OBJ_DIR)

$(OBJ_DIR) :
	mkdir obj
	mkdir obj/lexer
	mkdir obj/parser
	mkdir obj/debug
	mkdir obj/env
	mkdir obj/builtins
	mkdir obj/other
	mkdir obj/executor
	mkdir obj/bonus

bonus : $(MINISHELL_BONUS)
clean:
	$(RM) $(OBJ_DIR)
	make clean -C ./libft

fclean: clean
	$(RM) $(MINISHELL)
	$(RM) $(MINISHELL_BONUS)
	make fclean -C ./libft

re: fclean all

norm: $(SRC_FILES)
	norminette $<

.PHONY: all clean fclean re norm bonus
