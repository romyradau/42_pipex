FLAGS = -Wall -Wextra -Werror -I ./inc
NAME = pipex
BON_NAME = pipex_bonus
SRC = pipex.c exec.c
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OBJ_DIR = obj/
BON_SRC = pipex_bonus.c exec_bonus.c redirecting_bonus.c heredoc.c get_next_line.c get_next_line_utils.c
OBJ_BON = $(addprefix $(OBJ_DIR), $(BONUS:.c=.o))
BONUS = $(addprefix $(BON_DIR), $(BON_SRC))
BON_DIR = bonus/
LIBFT = libft/libft.a

all: $(NAME)


$(NAME): $(LIBFT) $(OBJ)
	gcc $(FLAGS) $(OBJ) $(LIBFT) -o $@

$(OBJ_DIR)%.o : %.c
	gcc -c $(FLAGS) $< -o $@

$(LIBFT) :
	@make -sC libft

clean:
	make -C libft clean
	rm -fr $(OBJ)

fclean:
	make -C libft fclean
	make clean
	rm -fr $(NAME) $(BON_NAME)
	rm -fr tmp_file
	rm -rf $(OBJ) $(OBJ_BON)

bonus: $(BON_NAME)

$(BON_NAME): $(LIBFT) $(OBJ_BON) $(BONUS)
	gcc $(FLAGS) $(OBJ_BON) $(LIBFT) -o $(BON_NAME)

re: fclean all