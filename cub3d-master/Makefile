# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/10 18:12:04 by cleticia          #+#    #+#              #
#    Updated: 2022/10/07 20:00:20 by lfranca-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = gcc

MLX	= ./src/mlx/minilibx-linux/libmlx.a

RM = rm -rf

INC = -I ./inc/ -I /src/lib/ -I ./src/mlx/minilibx-linux

FLAGS =	-Werror -Wall -Wextra

SRC = src/cub/main.c\
	src/cub/store_map.c\
    src/cub/validate_map.c\
    src/cub/game_loop.c\
	src/gnl/get_next_line.c\

OBJS = $(SRC:.c=.o)

LFT = ./src/lib/libft.a

LIB = -L ./src/lib/ -lft -L ./src/mlx/minilibx-linux -lmlx -lXext -lX11 -lm -lbsd

all: $(MLX) $(LFT) $(NAME)

$(NAME): $(LFT) $(OBJS)
	@$(CC) $(FLAGS) $(LFT) $(INC) $(OBJS) $(LIB) -o $@
	@echo "Ready!"

$(MLX):
	@make -s -C ./src/mlx/minilibx-linux
	@echo "Minilibx compiled!"

.c.o:
	@$(CC) -g $(FLAGS) -c $< -o $@

$(LFT):
	@echo "Compiling libft and cub3d..."
	@make bonus -s -C ./src/lib

clean:
	@make -s $@ -C ./src/lib
	@make -s $@ -C ./src/mlx/minilibx-linux
	@$(RM) $(OBJS)
	@echo "Clean done!"

fclean: clean
	@$(RM) $(NAME) $(OBJS) $(LFT)

re:	fclean all

.PHONY: all clean fclean re