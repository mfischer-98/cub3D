/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 17:21:31 by mefische          #+#    #+#             */
/*   Updated: 2026/06/10 17:03:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Checks if we have only digits in RGB numbers */
int	check_rgb_number(char **str)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			j = skip_spaces(str[i], j);
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
	char	*trimmed;

	rgb = ft_split(str, ',');
	if (!rgb)
		return (1);
	trimmed = ft_strtrim(rgb[0], " \t");
	if (check_rgb_number(rgb))
		return (free(trimmed), free_array(rgb), 1);
	if ((ft_atoi((trimmed)) > 255))
		return (free(trimmed), free_array(rgb), 1);
	if ((ft_atoi(rgb[1]) > 255))
		return (free(trimmed), free_array(rgb), 1);
	if ((ft_atoi(rgb[2]) > 255))
		return (free(trimmed), free_array(rgb), 1);
	// Usar RGB pa meter cor no teto/chao
	free_array(rgb);
	free(trimmed);
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
