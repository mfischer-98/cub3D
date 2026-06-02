/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:10:34 by mefische          #+#    #+#             */
/*   Updated: 2026/06/02 10:04:14 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* Writes a single pixel into the image buffer (game->data) instead of drawing directly to the window */
void	put_pixel(int x, int y, int color, t_game *game)
{
	int	i;

	if (x >= game->win_width || y >= game->win_height || x < 0 || y < 0) //pixels only inside the window
		return ;
	/* Compute the byte index of pixel (x, y) in the image buffer:
	*	- y * size_line → move down y rows (each row is size_line bytes)
	*	- x * (bpp / 8) → move right x pixels (bpp/8 = bytes per pixel) */
	i = y * game->size_line + x * game->bpp / 8;
	/* Write the color into the buffer, one byte at a time:
	*	- color & 0xFF → red (lowest 8 bits)
	*	- (color >> 8) & 0xFF → green (next 8 bits)
	*	- (color >> 16) & 0xFF → blue (next 8 bits) */
	game->data[i] = color & 0xFF;
	game->data[i + 1] = (color >> 8) & 0xFF;
	game->data[i + 2] = (color >> 16) & 0xFF;
	//mlx_pixel_put(game->mlx, game->win, x, y, color);
}

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

/* Clears old square when player moves */
void	clear_image(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->win_height)
	{
		x = 0;
		while (x < game->win_width)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}

int	draw_loop(t_game *game)
{
	int	i;
	double	step;
	double	angle;

	move_player(&game->player, &game->map);
	clear_image(game);
	// draw_map(game);
	// draw_square(((int)game->player.x * TEXT_SIZE),
	// 	((int)game->player.y * TEXT_SIZE), TEXT_SIZE, 0x00FF00, game);
	angle = game->player.angle - (PI / 6);
	step = (PI / 3) / game->win_width;
	i = 0;
	while(i < game->win_width)
	{
		ray_line(angle, i, game);
		angle += step;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

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
