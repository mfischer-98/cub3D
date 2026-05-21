# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/07 11:08:27 by mefische          #+#    #+#              #
#    Updated: 2026/05/21 16:21:45 by mefische         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

MLX_URL		= git@github.com:42paris/minilibx-linux

SRC = src/main.c src/init.c src/events.c src/free_data.c \
		src/parsing/parsing.c src/parsing/parsing_utils.c src/parsing/check_args.c  src/parsing/check_text.c src/parsing/check_rgbs.c 

MLX_PATH	= inc/mlx
MLX_ARC		= $(MLX_PATH)/libmlx_Linux.a
		
OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Werror -Wextra -Wall -g

LIBFT_DIR = inc/libft
LIBFT = $(LIBFT_DIR)/libft.a

all: get_mlx $(MLX_ARC) $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --silent

get_mlx:
	@echo "✨ $(CYA)Getting MLX submodule$(D)"
	@if test ! -d "$(MLX_PATH)"; then \
		git clone -q $(MLX_URL) $(MLX_PATH); \
	else \
		echo "🌸 $(GRN)MLX submodule already exists"; \
	fi

$(MLX_ARC): get_mlx
	@$(MAKE) -C $(MLX_PATH) > /dev/null 2>&1; true

$(NAME): $(OBJ)
		@echo "✨ Loading cub3D..."
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_ARC) -L/usr/lib/X11 -lXext -lX11 -lm -o $(NAME)
		@echo "✨ Game ready!"

%.o: %.c
		@$(CC) $(CFLAGS) -I$(MLX_PATH) -c $< -o $@

clean:
		@rm -f $(OBJ)
		@$(MAKE) -C $(LIBFT_DIR) clean --silent

fclean: clean
		@rm -f $(NAME)
		@$(MAKE) -C $(LIBFT_DIR) fclean --silent
		@echo "✅ cleanup done!"

mlxclean: fclean
	@rm -rf $(MLX_PATH)
	@echo "✅ MLX removed"

re: fclean all

.PHONY: all clean fclean re get_mlx mlxclean
