# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/08 20:37:33 by rschleic          #+#    #+#              #
#    Updated: 2022/01/18 21:30:13 by rschleic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
ft_tolower.c ft_toupper.c \
ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC)))
OBJ_DIR = obj/

all: $(NAME)

$(OBJ_DIR)%.o : %.c
	mkdir -p $$(dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	ar -crs $(NAME) $(OBJ)
clean:
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all
