/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:56:24 by mefische          #+#    #+#             */
/*   Updated: 2026/05/29 11:49:25 by mefische         ###   ########.fr       */
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

double	rotate_player(t_player *player, double angle_speed)
{
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

int	move_player(t_player *player, t_map *map)
{
	double	speed;
	double	angle_speed; // double is 8 bytes, can change to float 4bytes but less precise
	double	cos_angle = cos(player->angle);
	double	sin_angle = sin(player->angle);

	speed = 0.5;
	angle_speed = 0.5;
	angle_speed = rotate_player(player, angle_speed);
	if (not_wall(map, player->x, player->y - 1) && player->key_up)
	{
		player->x -= cos_angle * speed;
		player->y -= sin_angle * speed;
	}
	if (not_wall(map, player->x, player->y + 1) && player->key_down)
	{
		player->x += cos_angle * speed;
		player->y += sin_angle * speed;
	}
	if (not_wall(map, player->x + 1, player->y) && player->key_left)
	{
		player->x -= sin_angle * speed;
		player->y += cos_angle * speed;
	}
	if (not_wall(map, player->x - 1, player->y) && player->key_right)
	{
		player->x += sin_angle * speed;
		player->y -= cos_angle * speed;
	}
	return (0);
}
