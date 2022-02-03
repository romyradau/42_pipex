FAGS = 	-Wall -Wextra -Werror
NAME = 	pipex
SRC = 	pipex.c exec.c
BONUS = pipex_bonus.c 
LIBFT = libft/libft.a
OBJ = 	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	gcc $(FLAGS) $(OBJ) $(LIBFT) -o $@

$(LIBFT) :
	@make -sC libft > /dev/null

clean:
	make -C libft clean
	rm -fr $(OBJ)

fclean:
	make -C libft fclean
	make clean
	rm -fr $(NAME)
	rm -fr outfile
	rm -fr infile

bonus:


re: fclean all