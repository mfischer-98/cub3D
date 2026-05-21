/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 17:10:53 by mefische          #+#    #+#             */
/*   Updated: 2026/05/21 17:49:04 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
int not_identifier(char *line)
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

/* Skips spaces and checks if line is empty, identifiers and stores it in *map_config */
int	get_line(t_map *map, char *line, int *count)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (free(line), 0);
	if (not_identifier(line))
	{
		free(line);
		printf("Error\nInvalid identifiers\n");
		return (1);
	}
	trimmed = ft_strtrim(line, "\n");
	free(line);
	if (!trimmed)
		return (1);
	map->config[*count] = trimmed;
	(*count)++;
	return (0);
}

/* Checks and stores values for each texture */
int	read_config(char *map_file, t_map *map)
{
	int		fd;
	int		i;
	int		count;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (1);
	map->config = malloc(sizeof(char *) * (6 + 1));
	if (!map->config)
		return (close(fd), 1);
	count = 0;
	while (count < 6 && (line = get_next_line(fd)))
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (count == 6)
			break ;
		if (get_line(map, line, &count))
				return (close(fd), 1);
	}
	map->config[count] = NULL;
	close(fd);
	return (0);
}

/* Checks if the texture path is correct */
int check_textures(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->config[i])
	{
		j = 0;
		while (map->config[i][j] == ' ' || map->config[i][j] == '\t')
			j++;

		if (map->config[i][j] == 'N' || map->config[i][j] == 'S'
			|| map->config[i][j] == 'W' || map->config[i][j] == 'E')
		{
			if (check_fd(&map->config[i][j + 3], 't'))
			{
				printf("%s\n", &map->config[i][j + 3]);
				return (1);
			}
		}
		i++;
	} 
	return (0);
}
