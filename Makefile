# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anurgali <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/07 15:50:24 by anurgali          #+#    #+#              #
#    Updated: 2020/02/07 16:04:45 by anurgali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= wolf3d

CC		= gcc -g

FLAG	= -Wall -Wextra -Werror -g -O0 -fsanitize=address -fsanitize=undefined

SDL 	= -I include -L lib -l SDL2-2.0.0

SRCS	= main.c\
			drawmap.c\
			render_player.c\
			render_rays.c\

OBJ 	= ${SRCS:.c=.o}
INCLUDE = -I wolf.h -L ./libft -lft

all: $(NAME)

$(NAME): $(OBJ)
		@$(CC) -g $(FLAG) $(INCLUDE) $(SDL) $(OBJ) -o $(NAME)
clean:
				@/bin/rm -f $(OBJ)

fclean: clean
				@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean