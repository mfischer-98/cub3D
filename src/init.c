/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 14:43:30 by mefische          #+#    #+#             */
/*   Updated: 2026/05/29 15:39:08 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_player_angle(t_game *game)
{
	if (game->map.orient == 'N')
		game->player.angle = ( 3 * PI ) / 2;
	if (game->map.orient == 'S')
		game->player.angle = PI / 2;
	if (game->map.orient == 'W')
		game->player.angle = PI;
	if (game->map.orient == 'E')
		game->player.angle = 0;
}

void	init_player(t_player *player)
{
	player->angle = 0;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

t_game	init_game_data(void)
{
	t_game	game;

	game.mlx = NULL;
	game.win = NULL;
	game.win_width = 0;
	game.win_height = 0;
	game.map.design = NULL;
	game.data = NULL;
	game.img = NULL;
	game.bpp = 0;
	game.size_line = 0;
	game.endian = 0;
	game.map.design = NULL;
	game.map.config = NULL;
	game.map.width = 0;
	game.map.start = 0;
	game.map.height = 0;
	game.map.orient = 0;
	init_player(&game.player);
	game.texture.floor = 0;
	game.texture.ceiling = 0;
	return (game);
}
