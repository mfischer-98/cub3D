/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 17:10:53 by mefische          #+#    #+#             */
/*   Updated: 2026/06/18 15:38:16 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;

	if (line[i] == '\n' || line[i] == '\0')
		return (1);
	return (0);
}

/* Checks and stores values for each texture */
int	read_config(char **map_file, t_map *map)
{
	int		i;
	char	*trimmed;
	int		count;

	count = 0;
	i = 0;
	map->config = malloc (sizeof (char *) * 7);
	while (count < 6 && map_file[i])
	{
		if (is_empty_line(map_file[i]))
			i++;
		if (not_identifier(map_file[i]))
		{
			printf("Error\nInvalid identifiers\n");
			return (1);
		}
		else
		{
			trimmed = ft_strtrim(map_file[i], "\n");
			map->config[count] = ft_strdup(trimmed);
			free(trimmed);
			count++;
		}
		i++;
	}
	map->config[count] = NULL;
	return (0);
}

/* Checks if the texture path is correct */
int	check_textures(char **map_file, t_game *game, t_map *map)
{
	int	i;
	int	j;

	if (read_config(map_file, map))
		return (1);
	i = 0;
	while (map->config[i])
	{
		j = 0;
		j = skip_spaces(map->config[i], j);
		if (map->config[i][j] == 'N' || map->config[i][j] == 'S'
			|| map->config[i][j] == 'W' || map->config[i][j] == 'E')
		{
			j += 2;
			j = skip_spaces(map->config[i], j);
			if (check_fd(&map->config[i][j], 't'))
				return (1);
		}
		i++;
	}
	if (check_duplicates(map))
		return (1);
	if (check_colors(map, game))
		return (1);
	return (0);
}

/* Checks for duplicated identifiers, to have less lines I created the array */
int	check_duplicates(t_map *map)
{
	int	counter[6];
	int	i;

	counter[0] = 0;
	counter[1] = 0;
	counter[2] = 0;
	counter[3] = 0;
	counter[4] = 0;
	counter[5] = 0;
	i = 0;
	while (map->config[i])
	{
		id_count(map->config[i][0], counter);
		i++;
	}
	if (counter[0] != 1 || counter[1] != 1 || counter[2] != 1
		|| counter[3] != 1 || counter[4] != 1 || counter[5] != 1)
	{
		printf("Error\nInvalid identifiers\n");
		return (1);
	}
	return (0);
}

/* Checks if characters are the correct identifiers */
int	not_identifier(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return (0);
	if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return (0);
	if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		return (0);
	if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		return (0);
	if (line[i] == 'F' && line[i + 1] == ' ')
		return (0);
	if (line[i] == 'C' && line[i + 1] == ' ')
		return (0);
	return (1);
}