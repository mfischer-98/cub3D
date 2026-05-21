/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:04:43 by mefische          #+#    #+#             */
/*   Updated: 2026/05/21 18:04:19 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//BUG: garbage values in line, start is always 1
int	map_start(char *map_file)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		if (not_identifier(line) && !is_empty_line(line))
		{
			free(line);
			close(fd);
			return (i);
		}
		free(line);
		i++;
	}
	close(fd);
	return (0);
}

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
		i++;
	}
	close(fd);
	return (height);
}


void	read_map(char *map_file, t_map *map)
{
	int		fd;
	int		i;
	int		start;
	char	*line;

	start = map_start(map_file);
	printf("start = %d\n", start);
	map->height = map_height(start, map_file);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return ;
	map->design = malloc(sizeof(char *) * (map->height + 1));
	if (!map->design)
		return (close(fd), (void)1);
	i = 0;
	while (i < start)
	{
		line = get_next_line(fd);
		free(line);
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		line = get_next_line(fd);
		map->design[i] = ft_strtrim(line, "\n");
		printf("%s\n", map->design[i]);
		i++;
	}
	map->design[i] = NULL;
	close(fd);
}
