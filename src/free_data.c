/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:39:46 by mefische          #+#    #+#             */
/*   Updated: 2026/05/29 15:05:23 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_map(t_map *map)
{
	if (map->config)
		free_array(map->config);
	if (map->design)
		free_array(map->design);
}

void	free_data(t_game *game)
{
	free_map(&game->map);
}

// void	free_images(t_game *game)
// {
// 	if (game->img_wall_center1)
// 		mlx_destroy_image(game->mlx, game->img_wall_center1);
// }