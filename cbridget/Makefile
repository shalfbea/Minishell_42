HEADER := ../include/minishell.h

CC := clang

TestingFlags := -g3 #-fsanitize=address

FLAGS := -Wall -Wextra -Werror -I./../include -I../libft/include -pthread $(TestingFlags)

MINISHELL := minishell

LIBFT := ../libft/libft.a

SRC = executor.c ft_init.c open_pipes.c lib_lst.c main_test.c run_commands.c\
redirects.c check_cmd.c get_next_line_utils.c get_next_line.c heredoc.c heredoc02.c\
run_commands_utils.c builtins/builtins_utils.c builtins/builtins.c\
builtins/ft_export.c

OBJ_DIR = ./obj/
SRC_DIR = ./src/

SRC_FILES = $(addprefix $(SRC_DIR), $(SRC))

OBJ_FILES = $(patsubst %.c, %.o, $(addprefix $(OBJ_DIR), $(SRC)))

RM := rm -rf

.PHONY: all clean fclean re norm bonus

all: $(LIBFT) $(OBJ_DIR) $(HEADER) $(MINISHELL)

$(MINISHELL): $(LIBFT) $(HEADER) $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LIBFT) -o $(MINISHELL) -lreadline $(FLAGS)

$(LIBFT) :
	make -C ../libft

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR) :
	mkdir obj
	mkdir obj/builtins

clean:
	$(RM) $(OBJ_DIR)
	make clean -C ../libft

fclean: clean
	$(RM) $(MINISHELL)
	make fclean -C ../libft

re: fclean all

norm: $(SRC_FILES)
	norminette $<
