/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 09:09:27 by mefische          #+#    #+#             */
/*   Updated: 2026/06/02 10:48:24 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	touch(double px, double py, t_game *game)
{
	int	x;
	int	y;

	x = (int)(px / TEXT_SIZE);
	y = (int)(py / TEXT_SIZE);
	if (x < 0 || y < 0 || y >= game->map.height || x >= game->map.width)
		return (1);
	if (game->map.design[y][x] == '1')
		return (true);
	return (false);
}

double	distance(double x, double y)
{
	return (sqrt((x * x) + (y * y)));
}

double	fix_distance(double x1, double y1, double x2, double y2, t_game *game)
{
	double	delta_x;
	double	delta_y;
	double	angle;
	double	fix_dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist); 
}

void	ray_line(double angle, int i, t_game *game)
{
	double	dist;
	double	height;
	int		start_y;
	int		end;
	
	game->ray.ray_x = game->player.x * TEXT_SIZE + TEXT_SIZE / 2;
	game->ray.ray_y = game->player.y * TEXT_SIZE + TEXT_SIZE / 2;
	game->ray.cos_angle = cos(angle);
	game->ray.sin_angle = sin(angle);
	while (!touch(game->ray.ray_x, game->ray.ray_y, game))
	{
		game->ray.ray_x += game->ray.cos_angle;
		game->ray.ray_y += game->ray.sin_angle;
	}
	dist = fix_distance((game->player.x * TEXT_SIZE + TEXT_SIZE / 2), (game->player.y * TEXT_SIZE + TEXT_SIZE / 2), game->ray.ray_x, game->ray.ray_y, game);
	if (dist < 1)
		dist = 1;
	height = (TEXT_SIZE / dist) * (game->win_width / 2);
	start_y = (int)((game->win_height - height) / 2);
	end = (int)(start_y + height);
	while (start_y < end)
	{
		put_pixel(i, start_y, 255, game);
		start_y++;
	}
}
