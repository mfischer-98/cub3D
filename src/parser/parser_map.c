/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:04:43 by mefische          #+#    #+#             */
/*   Updated: 2026/05/26 15:53:45 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//BUG: garbage values in line, start is always 1
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
		printf("%s", line);
		start++;
		while (line[i] == ' ')
			i++;
		if (line[i] == '1')
		{
			free(line);
			close(fd);
			return (start);
		}
	}
	return (close(fd), start);
}

// Getting map height
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

//Get map width and put map in matrix
void	get_map_design(t_map *map, char *line, int fd)
{
	int	i;
	int	width;

	width = 0;
	i = 0;
	while (i < map->height)
	{
		line = get_next_line(fd);
		map->design[i] = line;
		line_trim(map->design[i]);
		width = line_len(map->design[i]);
		if (width > map->width)
			map->width = width;
		free(line);
		i++;
	}
	map->design[i] = NULL;
	printf("width = %d\n", map->width);
}

// Opening file and getting map height, start and values
void	read_map(char *map_file, t_map *map)
{
	int		fd;
	int		i;
	char	*line;

	map->start = map_start(map_file);
	map->height = map_height(map->start, map_file);
	printf("height = %d\n", map->height);
	printf("start = %d\n", map->start);
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
