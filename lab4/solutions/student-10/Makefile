NAME = filter
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./inc

SRC_DIR = src
SRCS = $(SRC_DIR)/main.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ../../../lab3-libft/solutions/student-10
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
