FAGS = 	-Wall -Wextra -Werror
NAME = 	pipex
SRC = 	pipex.c
LIBFT = libft/libft.a
OBJ = 	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT)
	gcc $(FLAGS) $(SRC) $(LIBFT) -o $@

$(LIBFT) :
	make --directory=./Libft

clean:
	make -C libft clean
	rm -fr $(OBJ)

fclean:
	make -C libft fclean
	make clean
	rm -fr $(NAME)

re: fclean all