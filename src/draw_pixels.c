/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:10:34 by mefische          #+#    #+#             */
/*   Updated: 2026/06/02 10:47:16 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* Writes a single pixel into the image buffer (game->data) instead of drawing directly to the window */
void	put_pixel(int x, int y, int color, t_game *game)
{
	char	*dist;

	if (x >= game->win_width || y >= game->win_height || x < 0 || y < 0) //pixels only inside the window
		return ;
	dist = game->data + (y * game->size_line + x * (game->bpp / 8));
	*(unsigned int *)dist = color;
}

/* Clears old square when player moves */
void	clear_image(t_game *game)
{
	ft_memset(game->data, 0, game->size_line * game->win_height);
}

int	draw_loop(t_game *game)
{
	int	i;
	double	step;
	double	angle;

	move_player(&game->player, &game->map);
	clear_image(game);
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
