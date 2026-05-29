/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:04:43 by mefische          #+#    #+#             */
/*   Updated: 2026/05/29 11:35:14 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Returns the number of the line where the map starts */
int	map_start(char *map_file)
{
	int		fd;
	int		i;
	int		start;
	char	*line;


	line = NULL;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	start = 0;
	while ((line = get_next_line(fd)))
	{
		start++;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '1')
		{
			free(line);
			return (close(fd), start);
		}
		free(line);
	}
	return (close(fd), start);
}

/* Returns the number the height of map so we can allocate memory in map design */
int	map_height(int start, char *map_file)
{
	int		fd;
	int		i;
	int		height;
	char	*line;

	height = 0;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		if (i >= start)
			height++;
		free(line);
		line = NULL;
		i++;
	}
	close(fd);
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
		line_trim(map->design[i]);
		width = line_len(map->design[i]);
		if (width > map->width)
			map->width = width;
		free(line);
		i++;
	}
	map->design[i] = NULL;
}

/* Opens map file and gets all the information so we have it in our map struct */
void	read_map(char *map_file, t_map *map)
{
	int		fd;
	int		i;
	char	*line;

	map->start = map_start(map_file) - 1;
	map->height = map_height(map->start, map_file) + 1;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return ;
	map->design = malloc(sizeof(char *) * (map->height + 1));
	if (!map->design)
		return (close(fd), (void)1);
	i = 0;
	while (i < map->start)
	{
		line = get_next_line(fd);
		free(line);
		i++;
	}
	get_map_design(map, line, fd);
	close(fd);
}

void	line_trim(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '\r') && (str[i + 1] == '\n'))
			str[i] = '\0';
		else if ((str[i] == '\n') && (str[i + 1] == '\0'))
			str[i] = '\0';
		i++;
	}
}
