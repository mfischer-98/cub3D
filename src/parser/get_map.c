/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:04:43 by mefische          #+#    #+#             */
/*   Updated: 2026/06/18 11:40:34 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Returns the number of the line where the map starts */
int	map_start(char **map_file)
{
	int		i;
	int		j;

	i = 0;
	while (map_file[i])
	{
		while (!not_identifier(map_file[i]))
			i++;
		j = 0;
		while (map_file[i][j])
		{
			while (map_file[i][j] == ' ' || map_file[i][j] == '\t')
				j++;
			if (map_file[i][j] == '1')
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}

/* Returns the number the height of map so we can
	allocate memory in map design */
int	map_height(int start, char **map_file)
{
	int		i;
	int		j;
	int		height;

	i = start;
	height = 0;
	while (map_file[i])
	{
		j = 0;
		while (map_file[i][j])
		{
			while (map_file[i][j] == ' ' || map_file[i][j] == '\t')
				j++;
			if (map_file[i][j] == '1')
			{
				height++;
				break ;
			}
			j++;
		}
		i++;
	}
	//if i++ && chamar !map_start, tem outro mapa
	//if map->height < 0
	return (height);
}

/* Puts line inside map->design, trims the \n and gets biggest width */
void	get_map_design(t_map *map, char *line, int fd)
{
	int		i;
	int		width;
	char	*temp;

	width = 0;
	i = 0;
	while (i < map->height)
	{
		line = get_next_line(fd);
		map->design[i] = ft_strdup(line);
		temp = convert_tabs(map->design[i]);
		free(map->design[i]);
		map->design[i] = temp;
		//line_trim(map->design[i]);
		width = line_len(map->design[i]);
		if (width > map->width)
			map->width = width;
		free(line);
		i++;
	}
	map->design[i] = NULL;
}

/* Opens map file and gets all the information
	so we have it in our map struct */
int	read_map(char **map_file, t_map *map)
{
	int		i;
	int		j;

	map->start = map_start(map_file);
	if (!map->start)
		return (printf("Error\nNo map identified\n"), 1);
	map->height = map_height(map->start, map_file);
	if (map->height < 3)
		return (printf("Error\nMap too small\n"), 1);
	map->design = malloc(sizeof(char *) * (map->height + 1));
	i = map->start;
	j = 0;
	while (map_file[i] && j < map->height)
	{
		map->design[j] = ft_strdup(map_file[i]);
		j++;
		i++;
	}
	map->design[j] = NULL;
	return (0);
}
