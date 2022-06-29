HEADER := include/minishell.h
SHALFBEA_HEADER := include/shalfbea_edit.h
CBRIDGET_HEADER := include/cbridget_edit.h
CC := cc

TestingFlags := -g3 #-fsanitize=address

#READLINE_LIB := -lreadline
INCLUDE_READLINE_HEADER = -I/Users/$(USER)/goinfre/.brew/opt/readline/include/readline
READLINE_LIB := $(INCLUDE_READLINE_HEADER) -L/Users/$(USER)/goinfre/.brew/Cellar/readline/8.1.2/lib/ -lreadline

FLAGS := -Wall -Wextra -Werror -I./include  -I./libft/include $(TestingFlags)

MINISHELL := minishell
MINISHELL_BONUS := minishell_bonus

LIBFT := libft/libft.a
LIBFT_HEADER := ./libft/include/libft.h

SRC = other/prompt.c other/signals.c other/ms_env.c \
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
	  builtins/new_lib.c \
	  lexer/wildcards.c \
	  debug/commands_printer.c debug/env_printer.c debug/groups_printer.c debug/lexer_printer.c

SRC_BONUS = bonus/logical.c bonus/stack_operations.c bonus/groups.c bonus/groups_execution.c bonus/bonus_main.c

OBJ_DIR = ./obj/
SRC_DIR = ./src/

SRC_FILES = $(addprefix $(SRC_DIR), $(SRC))
SRC_FILES_BONUS = $(addprefix $(SRC_DIR), $(SRC_BONUS))

OBJ_FILES = $(patsubst %.c, %.o, $(addprefix $(OBJ_DIR), $(SRC)))
OBJ_FILES_BONUS = $(OBJ_FILES) $(patsubst %.c, %.o, $(addprefix $(OBJ_DIR), $(SRC_BONUS)))

OBJ_STD = $(OBJ_FILES) $(OBJ_DIR)/main.o

RM := rm -rf

all: $(OBJ_DIR) $(HEADER) $(MINISHELL)

$(MINISHELL): $(HEADER) $(SHALFBEA_HEADER) $(CBRIDGET_HEADER) $(OBJ_STD) $(LIBFT)
	$(CC) $(FLAGS) $(READLINE_LIB) $(OBJ_STD) -o $(MINISHELL) $(LIBFT) $(READLINE_LIB)

$(MINISHELL_BONUS): $(HEADER) $(SHALFBEA_HEADER) $(CBRIDGET_HEADER) $(OBJ_FILES_BONUS) $(LIBFT)
	$(CC) $(FLAGS) $(READLINE_LIB) $(OBJ_FILES_BONUS) -o $(MINISHELL_BONUS) $(LIBFT) $(READLINE_LIB)

$(LIBFT) : $(LIBFT_HEADER)
	make -C ./libft

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) $(SHALFBEA_HEADER) $(CBRIDGET_HEADER)
	$(CC) $(FLAGS) $(INCLUDE_READLINE_HEADER) -c $< -o $@

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
