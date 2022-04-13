HEADER := include/minishell.h

CC := clang

TestingFlags := -g3 #-fsanitize=address

FLAGS := -Wall -Wextra -Werror -I./include -pthread $(TestingFlags)

MINISHELL := minishell

SRC = main.c #add more here

OBJ_DIR = ./obj/
SRC_DIR = ./src/

SRC_FILES = $(addprefix $(SRC_DIR), $(SRC))

OBJ_FILES = $(patsubst %.c, %.o, $(addprefix $(OBJ_DIR), $(SRC)))

RM := rm -rf

all: $(OBJ_DIR) $(HEADER) $(MINISHELL)

$(MINISHELL): $(HEADER) $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(MINISHELL)

$(LIBFT) :
	make -C ./libft

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR) :
	mkdir obj

clean:
	$(RM) $(OBJ_DIR)
	#make clean -C ./libft

fclean: clean
	$(RM) $(MINISHELL)

re: fclean all

norm: $(SRC_FILES)
	norminette $<

.PHONY: all clean fclean re norm bonus
