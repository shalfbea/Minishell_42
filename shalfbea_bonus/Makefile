HEADER := ../include/minishell.h

CC := clang

TestingFlags := -g3 #-fsanitize=address

READLINE_LIB := -I/Users/$(USER)/goinfre/.brew/Cellar/readline/8.1.2/include/ -L/Users/$(USER)/goinfre/.brew/Cellar/readline/8.1.2/lib/ -lreadline
FLAGS := -Wall -Wextra -Werror -I./../include -I../libft/include $(TestingFlags)

MINISHELL := minishell_bonus

LIBFT := ../libft/libft.a

SRC_MAIN = 	  other/prompt.c other/signals.c other/ms_env.c \
	  debug/printers.c \
	  lexer/lexer.c lexer/lexer_wraps_lst.c lexer/lexer_free.c \
	  lexer/lexer_specials.c lexer/token_gluer.c \
	  parser/parser.c parser/command_lst.c \
	  parser/char_arrays.c parser/string_arrays.c \
	  env/env_check.c env/env_finder.c \
	  executor/executor.c executor/ft_init.c executor/open_pipes.c executor/lib_lst.c \
	  executor/run_commands.c executor/redirects.c executor/check_cmd.c \
      executor/get_next_line_utils.c executor/get_next_line.c executor/heredoc.c executor/heredoc02.c \
      executor/run_commands_utils.c executor/heredoc_utils.c executor/put_error.c\
	  builtins/builtins_utils.c builtins/builtins.c builtins/ft_export.c \
	  builtins/ft_unset.c builtins/builtins_02.c builtins/retrieve_fd.c \
	  builtins/export_add_functions.c builtins/export_working_with_names.c\
	  lexer/wildcards.c
	  #builtins/exit.c

SRC_BONUS = main_shalfbea.c logical_tree_operations.c logical.c stack_operations.c

OBJ_DIR_MAIN = ../obj/
OBJ_DIR_BONUS = ./obj/
SRC_DIR_MAIN = ../src/
SRC_DIR_BONUS = ./src/

SRC_FILES_MAIN = $(addprefix $(SRC_DIR_MAIN), $(SRC_MAIN))
SRC_FILES_BONUS = $(addprefix $(SRC_DIR_BONUS), $(SRC_BONUS))

OBJ_FILES_MAIN = $(patsubst %.c, %.o, $(addprefix $(OBJ_DIR_MAIN), $(SRC_MAIN)))
OBJ_FILES_BONUS = $(patsubst %.c, %.o, $(addprefix $(OBJ_DIR_BONUS), $(SRC_BONUS)))

RM := rm -rf

all: $(MINISHELL)


$(MINISHELL): $(LIBFT) $(HEADER) $(OBJ_FILES_MAIN) $(OBJ_FILES_BONUS)
	$(CC) $(OBJ_FILES_MAIN) $(OBJ_FILES_BONUS) $(LIBFT) -o $(MINISHELL) $(READLINE_LIB) $(FLAGS)

$(LIBFT) :
	make -C ../libft

$(OBJ_DIR_MAIN)%.o: $(SRC_DIR_MAIN)%.c $(HEADER) $(OBJ_DIR_MAIN)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR_BONUS)%.o: $(SRC_DIR_BONUS)%.c $(HEADER) $(OBJ_DIR_BONUS)
	$(CC) $(FLAGS) -c $< -o $@


$(OBJ_DIR_MAIN) :
	mkdir ../obj/
	mkdir ../obj/lexer
	mkdir ../obj/parser
	mkdir ../obj/debug
	mkdir ../obj/env
	mkdir ../obj/builtins
	mkdir ../obj/other
	mkdir ../obj/executor

$(OBJ_DIR_BONUS) :
	mkdir ./obj/

clean:
	$(RM) $(OBJ_DIR_MAIN)
	$(RM) $(OBJ_DIR_BONUS)
	#make clean -C ./libft

fclean: clean
	$(RM) $(MINISHELL)
	#make fclean -C ./libft

re: fclean all

norm: $(SRC_FILES)
	norminette $<

.PHONY: all clean fclean re norm bonus
