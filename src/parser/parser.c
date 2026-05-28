/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 14:57:20 by mefische          #+#    #+#             */
/*   Updated: 2026/05/28 11:19:14 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Checks if there are blank lines inside the map */
int check_blank_lines (t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height - 1)
	{
		j = 0;
		j = skip_spaces(map->design[i], j);
		if (map->design[i][j] == '\n' || map->design[i][j] == '\0')
		{
			printf("Error\nBlank lines in map\n");
			return (1);
		}
		i++;
	}
	return (0);
}

/* Checks if map characters are valid: 1, 0, N, S, W, E */
int	check_chars(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->design[i])
	{
		j = 0;
		while (map->design[i][j])
		{
			j = skip_spaces(map->design[i], j);
			if (map->design[i][j] != '1' && map->design[i][j] != '0'
				&& map->design[i][j] != 'N' && map->design[i][j] != 'S'
				&& map->design[i][j] != 'E' && map->design[i][j] != 'W')
			{
				printf("Error\nInvalid map characters\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

/* Checks if we have one player spawning character */
int	check_player_char(t_map *map)
{
	int	i;
	int	j;
	int	counter;

	i = 0;
	counter = 0;
	while (map->design[i])
	{
		j = 0;
		while (map->design[i][j])
		{
			j = skip_spaces(map->design[i], j);
			if (map->design[i][j] == 'N' || map->design[i][j] == 'S'
				|| map->design[i][j] == 'E' || map->design[i][j] == 'W')
			{
				map->orient = map->design[i][j];
				counter++;
				if (counter != 1)
					return (printf("Error\nInvalid player characters\n"), 1);
			}
			j++;
		}
		i++;
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
	if (check_blank_lines(&game->map))
		return (1);
	if (check_chars(&game->map))
		return (1);
	if (check_player_char(&game->map))
		return (1);
	if (check_walls(&game->map, &game->player))
		return (1);
	return (0);
}
