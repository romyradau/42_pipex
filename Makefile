FLAGS = -Wall -Wextra -Werror
NAME = pipex
BON_NAME = pipex_bonus
SRC = pipex.c exec.c
BONUS = pipex_bonus.c exec_bonus.c redirecting_bonus.c heredoc.c get_next_line.c get_next_line_utils.c
OBJ_BON = $(addprefix $(OBJ_DIR),$(BONUS:.c=.o))
LIBFT = libft/libft.a
OBJ = $(addprefix $(OBJ_DIR),$(SRC:.c=.o))
OBJ_DIR = obj/

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
	rm -fr outfile
	rm -fr infile
	rm -fr tmp_file
	rm -rf $(OBJ) $(OBJ_BON)

bonus: $(BON_NAME)

$(BON_NAME) : $(LIBFT) $(OBJ_BON)
		gcc $(FLAGS) $(OBJ_BON) $(LIBFT) -o $@

re: fclean all