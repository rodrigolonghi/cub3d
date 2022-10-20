# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/07 20:10:29 by rfelipe-          #+#    #+#              #
#    Updated: 2022/10/17 19:50:20 by rfelipe-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
FLAGS = -g -Wall -Wextra -Werror
MLX_FLAGS = -lmlx -lXext -lX11
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --tool=memcheck -q ./cub3D map1.cub

LIBFT_DIR = ./libft
LIBFT = libft/libft.a

MLX_DIR = mlx_linux
MLX = mlx_linux/libmlx.a

SRC_DIR = src
SRC = $(SRC_DIR)/cub3d.c \
		$(SRC_DIR)/check_map.c \
		$(SRC_DIR)/check_params.c \
		$(SRC_DIR)/close_game.c \
		$(SRC_DIR)/key_hook.c \
		$(SRC_DIR)/calc.c \
		$(SRC_DIR)/color.c \
		$(SRC_DIR)/start_game.c \
		$(SRC_DIR)/vector.c \
		$(SRC_DIR)/player.c \
		$(SRC_DIR)/throw_error.c

INCLUDE_DIR = includes
INCLUDE = $(INCLUDE_DIR)/cub3d.h

OBJ_DIR = objs
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@$(CC) $(OBJ) $(LIBFT) -L$(MLX_DIR) $(MLX_FLAGS) -o $(NAME) -lm
	@echo "Cub3d compiled!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(FLAGS) -I$(INCLUDE_DIR) -o $@ $<

$(LIBFT):
	@echo "Compiling project...\n"
	@make -C $(LIBFT_DIR)

$(MLX):
	@echo "Compiling minilibx...\n"
	@make -C $(MLX_DIR)

clean:
	@make clean -C $(MLX_DIR)
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Deleting EVERYTHING...\n"
	@make fclean -C ./libft
	@rm -rf $(NAME)
	@echo "Project cleaned up!"

re: fclean all

valgrind: all
	@clear && $(VALGRIND)

v: valgrind

.PHONY:	all clean fclean re
