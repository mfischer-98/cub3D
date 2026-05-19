/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 14:57:20 by mefische          #+#    #+#             */
/*   Updated: 2026/05/19 17:16:03 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_chars(t_map *map);
int	check_walls(t_map *map);

int	parsing(int ac, char **args, t_game *game)
{
	if (check_number(ac))
		return (1);
	if (check_fd(args[1]))
		return (1);
	if (check_map_name(args[1]))
		return (1);
	read_config(args[1], game->map);
	if (check_textures(game->map, game->textures))
		return (1);
	// if (check_colors(game->map, game->textures))
	// 	return (1);
	// map_height(args[1], game->map);
	// read_map(args[1], game->map);
	//check_elements
	//check_chars
	//check_walls
	return (0);
}
