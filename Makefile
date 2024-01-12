SRC := get_next_line.c\
	   get_next_line_utils.c
OBJ := $(SRC:.c=.o)

CC := cc
CFLAGS := -Wall -Wextra -Werror -D BUFFER_SIZE=10000000

NAME := gnl

GDB := -g3
#ADDR := -fsanitize=address

.PHONY: all
all : $(NAME)

$(NAME): $(OBJ) main.o
	$(CC) $(GDB) $(ADDR) -o $@ $^

%.o: %.c
	$(CC) $(GDB) $(ADDR) $(CFLAGS) -I. -c $< -o $@

.PHONY: clean fclean re
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
