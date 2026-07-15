/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntomas-g <ntomas-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 12:04:39 by mefische          #+#    #+#             */
/*   Updated: 2026/07/15 10:23:44 by ntomas-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

/* Makes a square with pixels */
static void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(x + j, y + i, color, game);
			j++;
		}
		i++;
	}
}

/* Draws map squares according to map on corner of screen */
static void	draw_map(t_game *game, int block, int offset_x, int offset_y)
{
	int	y;
	int	x;

	y = 0;
	while (game->map.design[y])
	{
		x = 0;
		while (game->map.design[y][x])
		{
			if (game->map.design[y][x] == '1')
				draw_square(offset_x + x * block,
					offset_y + y * block, block, 0xFFFFFF, game);
			x++;
		}
		y++;
	}
}

/* Draws map and player as they move */
void	minimap(t_game *game)
{
	int	block;
	int	pos_x;
	int	pos_y;
	int	offset_x;
	int	offset_y;

	block = 12;
	offset_x = 20;
	offset_y = game->win_height - (game->map.height * block) - 20;
	pos_x = offset_x + (int)(game->player.x * block) + 1;
	pos_y = offset_y + (int)(game->player.y * block) + 1;
	draw_square(pos_x, pos_y, 4, 0xFA003F, game);
	draw_map(game, block, offset_x, offset_y);
}
