/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 17:10:53 by mefische          #+#    #+#             */
/*   Updated: 2026/05/19 17:22:08 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Skips spaces and checks if line is empty, identifiers and stores it in *map_config
int	get_line(t_map *map, char *line, int i)
{
	int	j;

	j = 0;
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	if ((line[j] == '\0' || line[j] == '\n'))
	{
		free(line);
		return (1);
	}
	if (!is_identifier(line))
	{
		free(line);
		return (1);
	}
	map_config[*i] = line;
	(*i)++;
	return (0);
}

// Checks and stores values for each texture
int	read_config(char *map_file, t_map *map)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (1);
	map->config = malloc(sizeof(char *) * (6 + 1));
	if (!map->config)
		return (close(fd), 1);
	i = 0;
	while (i < 6)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (get_line(map, line, &i))
			return (1);
	}
	map->config[i] = NULL;
	close(fd);
	if (i != 6)
		return (1);
	return (0);
}

int check_textures(t_map *map, t_textures *tex)
{
	int	i;
	int	j;

	i = 0;
	while (map->config[i])
	{
		j = 0;
		while (map->config[i][j])
		{
			if (map->config[i][j] == 'N')
			{
				if (check_path(map->config[i][j + 2]))
					return (1);
			}
			else if (map->config[i][j] == 'S')
			{
				if (check_path(map->config[i][j + 2]))
					return (1);
			}
			else if (map->config[i][j] == 'W')
			{
				if (check_path(map->config[i][j + 2]))
					return (1);
			}
			else if (map->config[i][j] == 'E')
			{
				if (check_path(map->config[i][j + 2]))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
