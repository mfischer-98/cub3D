/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 10:41:58 by mefische          #+#    #+#             */
/*   Updated: 2026/06/02 10:47:32 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* Draws the player square according to size and color passed */
void draw_square(int x, int y, int size, int color, t_game *game)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		put_pixel(x + i, y, color, game);
		put_pixel(x, y + i, color, game);
		put_pixel(x + size, y + i, color, game);
		put_pixel(x + i, y + size, color, game);
		i++;
	}
}

/* In draw_loop 
	// draw_map(game);
	// draw_square(((int)game->player.x * TEXT_SIZE),
	// 	((int)game->player.y * TEXT_SIZE), TEXT_SIZE, 0x00FF00, game); */
void	draw_map(t_game *game)
{
	int	color;
	int	i;
	int	j;

	color = 0x0000FF;
	i = 0;
	while (game->map.design[i])
	{
		j = 0;
		while (game->map.design[i][j])
		{
			if (game->map.design[i][j] == '1')
				draw_square(j * TEXT_SIZE, i * TEXT_SIZE, TEXT_SIZE, color, game);
			j++;
		}
		i++;
	}
}