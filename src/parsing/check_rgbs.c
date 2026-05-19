/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgbs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 17:21:31 by mefische          #+#    #+#             */
/*   Updated: 2026/05/19 17:21:50 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int check_colors(t_map *map, t_textures *tex)
{
	//quando achar F ou C ver se tem 3 números separados por ,
	//ver se está entre 0 e 255
	int	i;
	int	j;

	i = 0;
	while (map->config[i])
	{
		j = 0;
		while (map->config[i][j])
		{
			if (map->config[i][j] == 'F')
			if (map->config[i][j] == 'C')
			j++;
		}
		i++;
	}
}