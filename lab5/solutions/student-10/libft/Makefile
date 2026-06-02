NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./inc

SRCS = src/ft_isalpha.c \
       src/ft_isdigit.c \
       src/ft_isalnum.c \
       src/ft_isascii.c \
       src/ft_isprint.c \
       src/ft_strlen.c \
       src/ft_toupper.c \
       src/ft_tolower.c \
       src/ft_putchar_fd.c \
       src/ft_putstr_fd.c \
       src/ft_putendl_fd.c \
       src/ft_putnbr_fd.c \
       src/ft_isspace.c \
       src/ft_atoi.c \
       src/ft_bzero.c \
       src/ft_calloc.c \
       src/ft_memset.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
