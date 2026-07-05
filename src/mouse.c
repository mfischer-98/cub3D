/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                             :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: ntomas-g <ntomas-g@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 16:20:12 by ntomas-g         #+#    #+#              */
/*   Updated: 2026/07/05 14:29:00 by ntomas-g        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int g_last_mouse_x = -1;
static int g_last_mouse_y = -1;

static void update_camera_angle(t_player *player, double delta)
{
	player->angle += delta;
	while (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	while (player->angle < 0)
		player->angle += 2 * PI;
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	player->plane_x = -player->dir_y * 0.66;
	player->plane_y = player->dir_x * 0.66;
}

static void center_mouse_cursor(t_game *game)
{
	int	center_x;
	int	center_y;

	center_x = game->win_width / 2;
	center_y = game->win_height / 2;
	mlx_mouse_move(game->mlx, game->win, center_x, center_y);
}

void	look_left(t_player *player)
{
	update_camera_angle(player, -MOUSE_SPEED);
}

void	look_right(t_player *player)
{
	update_camera_angle(player, MOUSE_SPEED);
}

int	mouse_move(int x, int y, void *param)
{
	t_game	*game;

	if (!param)
		return (0);
	game = (t_game *)param;
	if (g_last_mouse_x < 0)
	{
		g_last_mouse_x = x;
		g_last_mouse_y = y;
		center_mouse_cursor(game);
		return (0);
	}
	if (x > g_last_mouse_x)
		look_right(&game->player);
	else if (x < g_last_mouse_x)
		look_left(&game->player);
	g_last_mouse_x = x;
	g_last_mouse_y = y;
	center_mouse_cursor(game);
	(void)y;
	return (0);
}

