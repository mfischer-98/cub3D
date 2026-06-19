/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 14:57:20 by mefische          #+#    #+#             */
/*   Updated: 2026/06/19 15:24:43 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Checks if there are blank lines inside the map */
int	check_blank_lines(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
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
			if (map->design[i][j] != '1' && map->design[i][j] != '0'
				&& map->design[i][j] != 'N' && map->design[i][j] != 'S'
				&& map->design[i][j] != 'E' && map->design[i][j] != 'W'
				&& map->design[i][j] != ' ')
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
			if (map->design[i][j] == 'N' || map->design[i][j] == 'S'
				|| map->design[i][j] == 'E' || map->design[i][j] == 'W')
			{
				map->orient = map->design[i][j];
				counter++;
			}
			j++;
		}
		i++;
	}
	if (counter != 1)
		return (printf("Error\nInvalid player characters\n"), 1);
	return (0);
}

int	parsing(int ac, char **args, t_game *game)
{
	char	**map_file;

	if (check_number(ac))
		return (1);
	if (check_fd(args[1], 'm'))
		return (1);
	if (check_map_name(args[1]))
		return (1);
	map_file = read_file(args[1]);
	if (!map_file)
		return (free_array(map_file), 1);
	if (check_textures(map_file, game, &game->map))
		return (free_array(map_file), 1);
	if (read_map(map_file, &game->map))
		return (free_array(map_file), 1);
	if (check_blank_lines(&game->map))
		return (free_array(map_file), 1);
	if (check_chars(&game->map))
		return (free_array(map_file), 1);
	if (check_player_char(&game->map))
		return (free_array(map_file), 1);
	if (check_walls(&game->map, &game->player))
		return (free_array(map_file), 1);
	free_array(map_file);
	return (0);
}
