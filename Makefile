# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/07 18:09:35 by chanykim          #+#    #+#              #
#    Updated: 2021/06/21 17:33:20 by chanykim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC_DIR = ./src/
SRC_NAME = main.c \
			util.c \
			time.c \
			error.c \
			init_info.c



SRC = $(addprefix $(SRC_DIR),$(SRC_NAME))

OBJ_DIR = ./obj/
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_DIR),$(OBJ_NAME))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
INCLUDE = -I./src/include

all : $(NAME)

clean :
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)
fclean : clean
	rm -f $(NAME)
re : fclean all

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@

.PHONY : all clean fclean
