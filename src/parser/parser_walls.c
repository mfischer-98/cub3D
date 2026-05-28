/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:07:53 by mefische          #+#    #+#             */
/*   Updated: 2026/05/28 11:18:13 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Gets player position and adds it to player struct */
void	find_player(t_map *map, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height - 1)
	{
		j = 0;
		while (map->design[i][j] && map->design[i][j] != '\n')
		{
			if (map->design[i][j] == map->orient)
			{
				player->row = i;
				player->col = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

/* Turns 0 into Fs and then checks 
	- If I leave map with flood fill = open_map (return 0)
	- If I get to a space = open_map (return 0) */
int	flood_fill(t_map *map, char **map_copy, int i, int j)
{
	if (i < 0 || j < 0 || i >= map->height || j >= map->width)
		return (0);
	if (map_copy[i][j] == ' ')
		return (0);
	if (map_copy[i][j] == 'F' || map_copy[i][j] == '1')
		return (1);
	map_copy[i][j] = 'F';
	if (!flood_fill(map, map_copy, i - 1, j))
		return (0);
	if (!flood_fill(map, map_copy, i + 1, j))
		return (0);
	if (!flood_fill(map, map_copy, i, j - 1))
		return (0);
	if (!flood_fill(map, map_copy, i, j + 1))
		return (0);
	return (1);
}

/* Gets player position and validates flood_fill, returns error if walls are open */
int	check_walls(t_map *map, t_player *player)
{
	char	**map_copy;
	int		closed;

	find_player(map, player);
	map_copy = copy_array(map);
	map_copy[player->row][player->col] = '0';
	closed = flood_fill(map, map_copy, player->row, player->col);
	free_array(map_copy);
	if (!closed)
	{
		printf("Error\nMap not enclosed by walls\n");
		return (1);
	}
	return (0);
}

static void	copy_row(t_map *map, char *row, int i)
{
	int	j;
	int	len;

	len = ft_strlen(map->design[i]);
	j = 0;
	while (j < map->width)
	{
		if (j < len)
			row[j] = map->design[i][j];
		else
			row[j] = ' ';
		j++;
	}
	row[j] = '\0';
}

char	**copy_array(t_map *map)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (map->height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		copy[i] = malloc(sizeof(char) * (map->width + 1));
		if (!copy[i])
			return (NULL);
		copy_row(map, copy[i], i);
		printf("%s\n", copy[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
