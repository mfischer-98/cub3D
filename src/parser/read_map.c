/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 09:36:02 by mefische          #+#    #+#             */
/*   Updated: 2026/06/18 11:38:39 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Opens map file and gets its contents */
char	**read_file(char *file)
{
	int		fd;
	int		i;
	int		count;
	char	*line;
	char	**map_file;

	count = count_lines(file);
	map_file = malloc (sizeof (char *) * (count + 1));
	if (!map_file)
	{
		printf("Error\nEmpty File\n");
		return (NULL);
	}
	fd = open(file, O_RDONLY);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		map_file[i] = ft_strdup(line);
		line = get_next_line(fd);
		i++;
	}
	map_file[i] = NULL;
	return (close(fd), map_file);
}

/* Count lines in file so we can allocate memory */
int	count_lines(char *file)
{
	int	fd;
	int	count;
	char *line;

	count = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		line = get_next_line(fd);
		free(line);
		count++;
	}
	close(fd);
	return (count);
}
