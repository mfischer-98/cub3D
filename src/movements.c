/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:56:24 by mefische          #+#    #+#             */
/*   Updated: 2026/05/29 10:52:00 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	move_player(t_player *player, t_map *map)
{
	double	speed;

	speed = 0.1;

	// Add conditon && map != 1
	if (player->key_up && map->design[(int)player->y - 1][(int)player->x] != '1')
		player->y -= speed;
	if (player->key_down && map->design[(int)player->y + 1][(int)player->x] != '1')
		player->y += speed;
	if (player->key_left && map->design[(int)player->y][(int)player->x - 1] != '1')
		player->x -= speed;
	if (player->key_right && map->design[(int)player->y][(int)player->x + 1] != '1')
		player->x += speed;
	return (0);
}
