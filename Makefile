# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/07 11:08:27 by mefische          #+#    #+#              #
#    Updated: 2026/07/05 13:48:18 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

BONUS	= .bonus_build
MLX_URL	= git@github.com:42paris/minilibx-linux

SRC = src/main.c src/init.c src/events.c src/free_data.c src/render.c src/movements.c src/mouse.c src/ray.c src/ray_utils.c \
		src/load_textures.c src/render_walls.c src/fog.c \
		src/parser/parser.c src/parser/parser_utils.c src/parser/parser_args.c  src/parser/parser_textures.c src/parser/parser_colors.c \
		src/parser/get_map.c src/parser/parser_walls.c src/parser/read_map.c 

BONUS_SRC = src_bonus/main.c src_bonus/init.c src_bonus/events.c src_bonus/free_data.c src_bonus/render.c src_bonus/movements.c src_bonus/ray.c src_bonus/ray_utils.c \
		src_bonus/load_textures.c src_bonus/render_walls.c src_bonus/fog.c \
		src_bonus/parser/parser.c src_bonus/parser/parser_utils.c src_bonus/parser/parser_args.c  src_bonus/parser/parser_textures.c src_bonus/parser/parser_colors.c \
		src_bonus/parser/get_map.c src_bonus/parser/parser_walls.c src_bonus/parser/read_map.c 

MLX_PATH	= inc/mlx
MLX_ARC		= $(MLX_PATH)/libmlx_Linux.a
		
OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

CC = cc
CFLAGS = -Werror -Wextra -Wall -g

LIBFT_DIR = inc/libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

bonus: $(BONUS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --silent

get_mlx:
	@if test ! -d "$(MLX_PATH)"; then \
		echo "🌸 Getting MLX submodule"; \
		git clone -q $(MLX_URL) $(MLX_PATH); \
	fi

$(MLX_ARC): get_mlx
	@$(MAKE) -C $(MLX_PATH) > /dev/null 2>&1; true

$(NAME): $(OBJ) $(LIBFT) $(MLX_ARC)
		@echo "✨ Loading cub3D..."
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_ARC) -L/usr/lib/X11 -lXext -lX11 -lm -o $(NAME)
		@rm -f $(BONUS)
		@echo "✨ Game ready!"

$(BONUS): $(BONUS_OBJ) $(LIBFT) $(MLX_ARC)
	@echo "✨ Loading cub3D bonus..."
	@$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) $(MLX_ARC) -L/usr/lib/X11 -lXext -lX11 -lm -o $(NAME)
	@touch $(BONUS)
	@echo "✨ Bonus game ready!"

%.o: %.c | $(MLX_ARC)
		@$(CC) $(CFLAGS) -I$(MLX_PATH) -c $< -o $@

clean:
		@rm -f $(OBJ) $(BONUS_OBJ)
		@$(MAKE) -C $(LIBFT_DIR) clean --silent

fclean: clean
		@rm -f $(NAME) $(BONUS)
		@$(MAKE) -C $(LIBFT_DIR) fclean --silent
		@echo "✅ cleanup done!"

mlxclean: fclean
	@rm -rf $(MLX_PATH)
	@echo "✅ MLX removed"

re: fclean all

.PHONY: all bonus clean fclean re get_mlx mlxclean
