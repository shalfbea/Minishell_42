NAME := libft.a

HEADER := include/libft.h

CC := gcc

FLAGS := -Wall -Werror -Wextra -I./include

SRC_STD = $(addprefix std_functions/, ft_strlen.c ft_strchr.c ft_strlcpy.c ft_strrchr.c ft_strncmp.c ft_strlcat.c ft_strnstr.c\
			ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
			ft_toupper.c ft_tolower.c ft_bzero.c ft_atoi.c\
			ft_memset.c	ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
			ft_calloc.c ft_strdup.c ft_striteri.c \
			ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
			ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
			ft_putnbr_fd.c) \

SRC_LST = $(addprefix lst_functions/, ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
				  ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
				  ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c)

OBJ_STD = $(patsubst %.c, %.o, $(SRC_STD))
OBJ_LST = $(patsubst %.c, %.o, $(SRC_LST))
RM := rm -rf

all: $(NAME) $(OBJ) $(HEADER)

$(NAME) : $(OBJ_STD) $(OBJ_LST)
	ar rcs $(NAME) $?

%.o : %.c
	gcc $(FLAGS) -c $< -o $@

all_bonus :
	ar rcs $(NAME) $?

bonus : all
	make OBJ="$(OBJ_LST)"

clean:
	$(RM) $(OBJ_STD) $(OBJ_LST)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norm:
	norminette -R CheckDefine libft.h
	norminette -R CheckForbiddenSourceHeader *.c

.PHONY: all clean fclean re norm bonus
