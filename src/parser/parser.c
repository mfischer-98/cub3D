/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 14:57:20 by mefische          #+#    #+#             */
/*   Updated: 2026/05/27 11:15:28 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int check_blank_lines (t_map *map)
{
	int	x;
	int	y;

	x = 0;
	while (map->design[x])
	{
		y = 0;
		while (map->design[x][y])
		{
			while (map->design[x][y] == ' ' || map->design[x][y] == '\t')
				y++;
			if (map->design[x][y] == '\n' || map->design[x][y] == '\0')
			{
				printf("Error\nBlank lines in map\n");
				return (1);
			}
			y++;
		}
		x++;
	}
	return (0);
}

int	check_chars(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	while (map->design[x])
	{
		y = 0;
		while (map->design[x][y])
		{
			while (map->design[x][y] == ' ' || map->design[x][y] == '\t')
				y++;
			if (map->design[x][y] != '1' && map->design[x][y] != '0'
				&& map->design[x][y] != 'N' && map->design[x][y] != 'S'
				&& map->design[x][y] != 'E' && map->design[x][y] != 'W')
			{
				printf("Error\nInvalid map characters\n");
				return (1);
			}
			y++;
		}
		x++;
	}
	return (0);
}

int	check_player_char(t_map *map)
{
	int	x;
	int	y;
	int	counter;

	x = 0;
	counter = 0;
	while (map->design[x])
	{
		y = 0;
		while (map->design[x][y])
		{
			while (map->design[x][y] == ' ' || map->design[x][y] == '\t')
				y++;
			if (map->design[x][y] == 'N' || map->design[x][y] == 'S'
				|| map->design[x][y] == 'E' || map->design[x][y] == 'W')
			{
				map->orient = map->design[x][y];
				counter++;
				if (counter > 1)
					return (printf("Error\nToo many players in map\n"), 1);
			}
			y++;
		}
		x++;
	}
	return (0);
}

int	parsing(int ac, char **args, t_game *game)
{
	if (check_number(ac))
		return (1);
	if (check_fd(args[1], 'm'))
		return (1);
	if (check_map_name(args[1]))
		return (1);
	if (read_config(args[1], &game->map))
		return (1);
	if (check_textures(&game->map))
		return (1);
	if (check_duplicates(&game->map))
		return (1);
	if (check_colors(&game->map))
		return (1);
	read_map(args[1], &game->map);
	if (check_blank_lines(&game->map)) //need to check if after map there are lines
		return (1);
	if (check_chars(&game->map))
		return (1);
	if (check_player_char(&game->map))
		return (1);
	//check_format, precisa?? min max?
	//check_walls are closed
	return (0);
}
