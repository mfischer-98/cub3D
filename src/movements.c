/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:56:24 by mefische          #+#    #+#             */
/*   Updated: 2026/06/08 17:44:44 by marvin           ###   ########.fr       */
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

double	rotate_player(t_player *player)
{
	if (player->left_rotate)
		player->angle -= ANGLE_SPEED;
	if (player->right_rotate)
		player->angle += ANGLE_SPEED;
	while (player->angle > 2 * PI) // Need to normalize the angle so it is within a circle 2PI
		player->angle = 0;
	while (player->angle < 0) // Completing the circle
		player->angle = 2 * PI;
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
