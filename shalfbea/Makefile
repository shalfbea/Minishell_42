HEADER := ../include/minishell.h

CC := clang

TestingFlags := -g3 #-fsanitize=address

FLAGS := -Wall -Wextra -Werror -I./../include -I../libft/include -pthread $(TestingFlags)

MINISHELL := minishell

LIBFT := ../libft/libft.a

SRC = main_shalfbea.c \
	  prompt.c \
	  signals.c \
	  ms_env.c \
	  debug/printers.c \
	  lexer/lexer.c lexer/lexer_wraps_lst.c lexer/lexer_specials.c \
	  lexer/env_check.c \
	  parser/parser.c parser/arrays.c parser/command_lst.c \
	  parser/logical_groups.c
	  #builtins/exit.c

OBJ_DIR = ./obj/
SRC_DIR = ./src/

SRC_FILES = $(addprefix $(SRC_DIR), $(SRC))

OBJ_FILES = $(patsubst %.c, %.o, $(addprefix $(OBJ_DIR), $(SRC)))

RM := rm -rf

all: $(LIBFT) $(OBJ_DIR) $(HEADER) $(MINISHELL)

$(MINISHELL): $(LIBFT) $(HEADER) $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LIBFT) -o $(MINISHELL) -lreadline $(FLAGS)

$(LIBFT) :
	make -C ../libft

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR) :
	mkdir obj
	mkdir obj/lexer
	mkdir obj/parser
	mkdir obj/debug

clean:
	$(RM) $(OBJ_DIR)
	make clean -C ../libft

fclean: clean
	$(RM) $(MINISHELL)
	make fclean -C ../libft

re: fclean all

norm: $(SRC_FILES)
	norminette $<

.PHONY: all clean fclean re norm bonus
