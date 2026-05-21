/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgbs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 17:21:31 by mefische          #+#    #+#             */
/*   Updated: 2026/05/21 16:47:46 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Checks if we have only digits in RGB numbers */
int	check_rgb_number(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	if (i != 3)
		return (1);
	return (0);
}

/* Splits RGB and checks if numbers are below 256 */
int	check_rgb_format(char *str)
{
	char	**rgb;

	rgb = ft_split(str, ',');
	if (!rgb)
		return (1);
	if (check_rgb_number(rgb))
		return (free_array(rgb), 1);
	if ((ft_atoi(rgb[0]) > 255))
		return (free_array(rgb), 1);
	if ((ft_atoi(rgb[1]) > 255))
		return (free_array(rgb), 1);
	if ((ft_atoi(rgb[2]) > 255))
		return (free_array(rgb), 1);
	free_array(rgb);
	return (0);
}

/* Gets RGB from map->config and returns error if invalid */
int	check_colors(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->config[i])
	{
		j = 0;
		while (map->config[i][j])
		{
			if (map->config[i][j] == 'F' || map->config[i][j] == 'C')
			{
				if (check_rgb_format(&map->config[i][j + 2]))
				{
					printf("Error\nInvalid RGB value\n");
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}