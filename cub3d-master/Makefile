# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/10 18:12:04 by cleticia          #+#    #+#              #
#    Updated: 2022/09/04 04:26:27 by cleticia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = gcc

RM = rm -rf

INC = -I ./inc/ -I /src/lib/ 

FLAGS =	-Werror -Wall -Wextra

SRC = src/cub/main.c\
	src/cub/store_map.c\
    src/cub/validate_map.c\
    src/cub/game_loop.c\
	src/gnl/get_next_line.c\

OBJS = $(SRC:.c=.o)

LFT = ./src/lib/libft.a

LIB = -L ./src/lib/ -lft -L/usr/include

all: $(NAME)

$(NAME): $(LFT) $(OBJS)
	@$(CC) $(FLAGS) $(LFT) $(INC) $(OBJS) $(LIB) -o $@
	@echo "Ready!"

.c.o:
	@$(CC) -g $(FLAGS) -c $< -o $@

$(LFT):
	@echo "Compiling libft and cub3d..."
	@make bonus -s -C ./src/lib

clean:
	@make -s $@ -C ./src/lib
	@$(RM) $(OBJS)
	@echo "Clean done!"

fclean: clean
	@$(RM) $(NAME) $(OBJS) $(LFT)

re:	fclean all

.PHONY: all clean fclean re