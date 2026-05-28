/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:07:53 by mefische          #+#    #+#             */
/*   Updated: 2026/05/28 11:00:36 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Gets player position and adds it to player struct */
void	find_player(t_map *map, t_player *player)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height - 1)
	{
		x = 0;
		while (map->design[y][x] && map->design[y][x] != '\n')
		{
			if (map->design[y][x] == map->orient)
			{
				player->pos_x = x;
				player->pos_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

/* Turns 0 into Fs and then checks 
	- If I leave map with flood fill = open_map (return 0)
	- If I get to a space = open_map (return 0) */
int	flood_fill(t_map *map, char **map_copy, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (0);
	if (map_copy[y][x] == ' ')
		return (0);
	if (map_copy[y][x] == 'F' || map_copy[y][x] == '1')
		return (1);
	map_copy[y][x] = 'F';
	if (!flood_fill(map, map_copy, x - 1, y))
		return (0);
	if (!flood_fill(map, map_copy, x + 1, y))
		return (0);
	if (!flood_fill(map, map_copy, x, y - 1))
		return (0);
	if (!flood_fill(map, map_copy, x, y + 1))
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
	map_copy[player->pos_y][player->pos_x] = '0';
	closed = flood_fill(map, map_copy, player->pos_x, player->pos_y);
	free_array(map_copy);
	if (!closed)
	{
		printf("Error\nMap not enclosed by walls\n");
		return (1);
	}
	return (0);
}

static void	copy_row(t_map *map, char *row, int y)
{
	int	x;
	int	len;

	len = ft_strlen(map->design[y]);
	x = 0;
	while (x < map->width)
	{
		if (x < len)
			row[x] = map->design[y][x];
		else
			row[x] = ' ';
		x++;
	}
	row[x] = '\0';
}

char	**copy_array(t_map *map)
{
	char	**copy;
	int		y;

	copy = malloc(sizeof(char *) * (map->height + 1));
	if (!copy)
		return (NULL);
	y = 0;
	while (y < map->height)
	{
		copy[y] = malloc(sizeof(char) * (map->width + 1));
		if (!copy[y])
			return (NULL);
		copy_row(map, copy[y], y);
		printf("%s\n", copy[y]);
		y++;
	}
	copy[y] = NULL;
	return (copy);
}
