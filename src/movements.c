/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:56:24 by mefische          #+#    #+#             */
/*   Updated: 2026/06/15 16:34:08 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	not_wall(t_map *map, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0 || map_y >= map->height || map_x >= map->width)
		return (0);
	if (map->design[map_y][map_x] == '1')
		return (0);
	return (1);
}

/* Player rotation
	- If > 2PI, need to normalize so it is in the circle
	- If = 0, completed circle */
double	rotate_player(t_player *player)
{
	if (player->left_rotate)
		player->angle -= ANGLE_SPEED;
	if (player->right_rotate)
		player->angle += ANGLE_SPEED;
	while (player->angle > 2 * PI)
		player->angle = 0;
	while (player->angle < 0)
		player->angle = 2 * PI;
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	player->plane_x = -player->dir_y * 0.66;
	player->plane_y = player->dir_x * 0.66;
	return (ANGLE_SPEED);
}

void	move_vertical(t_player *player, t_map *map)
{
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->key_up)
	{
		if (not_wall(map, player->x + cos_angle * SPEED, player->y))
			player->x += cos_angle * SPEED;
		if (not_wall(map, player->x, player->y + sin_angle * SPEED))
			player->y += sin_angle * SPEED;
	}
	if (player->key_down)
	{
		if (not_wall(map, player->x - cos_angle * SPEED, player->y))
			player->x -= cos_angle * SPEED;
		if (not_wall(map, player->x, player->y - sin_angle * SPEED))
			player->y -= sin_angle * SPEED;
	}
}

void	move_horizontal(t_player *player, t_map *map)
{
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->key_right)
	{
		if (not_wall(map, player->x - sin_angle * SPEED, player->y))
			player->x -= sin_angle * SPEED;
		if (not_wall(map, player->x, player->y + cos_angle * SPEED))
			player->y += cos_angle * SPEED;
	}
	if (player->key_left)
	{
		if (not_wall(map, player->x + sin_angle * SPEED, player->y))
			player->x += sin_angle * SPEED;
		if (not_wall(map, player->x, player->y - cos_angle * SPEED))
			player->y -= cos_angle * SPEED;
	}
}

int	move_player(t_player *player, t_map *map)
{
	rotate_player(player);
	move_vertical(player, map);
	move_horizontal(player, map);
	return (0);
}
