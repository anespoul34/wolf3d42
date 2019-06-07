#
#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anespoul <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/02 11:58:05 by anespoul          #+#    #+#              #
#    Updated: 2016/03/21 13:40:05 by anespoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re norme

NAME = wolf3d

FLAGS = -lmlx -O3 -framework OpenGL -framework AppKit

SRC = ./libft/libft.a error.c draw.c main.c raycast.c key_events.c \
	  move.c

LIB =-L libft

all: $(NAME)

$(NAME):
	make -C libft/
	gcc -o $(NAME) $(SRC) $(FLAGS)

clean:
	make -C libft clean

fclean: clean
	make -C libft fclean
	rm -fv $(NAME)

re: fclean all

norme:
	norminette $(SRC)
