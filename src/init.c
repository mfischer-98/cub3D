/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 14:43:30 by mefische          #+#    #+#             */
/*   Updated: 2026/05/26 12:13:58 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_game	init_game(void)
{
	t_game	game;

	game.mlx = NULL;
	game.win = NULL;
	game.map.design = NULL;
	game.map.width = 0;
	game.map.start = 0;
	game.map.height = 0;
	game.map.orient = 0;
	game.player.pos_x = 0;
	game.player.pos_y = 0;
	game.texture.floor = 0;
	game.texture.ceiling = 0;
	return (game);
}
