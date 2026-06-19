/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:04:43 by mefische          #+#    #+#             */
/*   Updated: 2026/06/19 11:08:39 by mefische         ###   ########.fr       */
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
			if (map_file[i][j] == '1' || map_file[i][j] == '0')
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
			if (map_file[i][j] == '1' || map_file[i][j] == '0')
			{
				height++;
				break ;
			}
			j++;
		}
		i++;
	}
	return (height);
}

/* Puts line inside map->design, trims the \n and gets biggest width */
void	get_map_width(t_map *map)
{
	int		i;
	int		width;
	int		len;
	char	*temp;

	width = 0;
	i = 0;
	while (map->design[i])
	{
		temp = map->design[i];
		map->design[i] = convert_tabs(temp);
		len = ft_strlen(map->design[i]);
		if (len > width)
			width = len;
		free (temp);
		i++;
	}
	map->width = width;
}

/* Opens map file and gets all the information
	so we have it in our map struct */
int	read_map(char **map_file, t_map *map)
{
	int		i;
	int		j;
	char	*trimmed;

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
		trimmed = ft_strtrim(map_file[i], "\n");
		map->design[j] = ft_strdup(trimmed);
		free(trimmed);
		j++;
		i++;
	}
	map->design[j] = NULL;
	get_map_width(map);
	return (0);
}
