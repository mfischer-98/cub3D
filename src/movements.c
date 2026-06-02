/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:56:24 by mefische          #+#    #+#             */
/*   Updated: 2026/06/02 10:05:11 by mefische         ###   ########.fr       */
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
	double	angle_speed; // double is 8 bytes, can change to float 4bytes but less precise

	angle_speed = 0.02;
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI) // Need to normalize the angle so it is within a circle 2PI
		player->angle = 0;
	if (player->angle < 0) // Completing the circle
		player->angle = 2 * PI;
	return (angle_speed);
}

void	move_vertical(t_player *player, t_map *map, double speed)
{
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->key_up)
	{
		if (not_wall(map, player->x + cos_angle * speed, player->y))
			player->x += cos_angle * speed;
		if (not_wall(map, player->x, player->y + sin_angle * speed))
			player->y += sin_angle * speed;
	}
	if (player->key_down)
	{
		if (not_wall(map, player->x - cos_angle * speed, player->y))
			player->x -= cos_angle * speed;
		if (not_wall(map, player->x, player->y - sin_angle * speed))
			player->y -= sin_angle * speed;
	}
}

void	move_horizontal(t_player *player, t_map *map, double speed)
{
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->key_right)
	{
		if (not_wall(map, player->x - sin_angle * speed, player->y))
			player->x -= sin_angle * speed;
		if (not_wall(map, player->x, player->y + cos_angle * speed))
			player->y += cos_angle * speed;
	}
	if (player->key_left)
	{
		if (not_wall(map, player->x + sin_angle * speed, player->y))
			player->x += sin_angle * speed;
		if (not_wall(map, player->x, player->y - cos_angle * speed))
			player->y -= cos_angle * speed;
	}
}

int	move_player(t_player *player, t_map *map)
{
	double	speed;

	speed = 0.05;
	rotate_player(player);
	move_vertical(player, map, speed);
	move_horizontal(player, map, speed);
	return (0);
}
