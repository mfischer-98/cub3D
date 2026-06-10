/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntomas-g <ntomas-g@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 14:43:30 by mefische          #+#    #+#             */
/*   Updated: 2026/06/10 17:24:42 by ntomas-g         ###   ########.fr       */
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

void	init_ray(t_ray *ray)
{
	ray->pos_x = 0;
	ray->pos_y = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->delta_x = 0;
	ray->delta_y = 0;
	ray->side_x = 0;
	ray->side_y = 0;
	ray->hit = 0;
	ray->side = 0;
	ray->p_dist = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
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
	init_ray(&game.ray);
	game.texture.floor = 0x524336;
	game.texture.ceiling = 0x000000;
	return (game);
}
