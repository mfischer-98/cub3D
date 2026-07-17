/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 17:21:31 by mefische          #+#    #+#             */
/*   Updated: 2026/07/17 19:29:06 by mefische         ###   ########.fr       */
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
			if (str[i][j] && !ft_isdigit(str[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	if (i != 3)
		return (1);
	return (0);
}

void	add_values(char **rgb, char c, t_game *game)
{
	char	*trimmed;

	trimmed = ft_strtrim(rgb[0], " \t");
	if (c == 'f')
	{
		game->texture.floor[0] = ft_atol_rgb((trimmed));
		game->texture.floor[1] = ft_atol_rgb((rgb[1]));
		game->texture.floor[2] = ft_atol_rgb((rgb[2]));
	}
	else
	{
		game->texture.ceiling[0] = ft_atol_rgb((trimmed));
		game->texture.ceiling[1] = ft_atol_rgb((rgb[1]));
		game->texture.ceiling[2] = ft_atol_rgb((rgb[2]));
	}
	free(trimmed);
}

/* Splits RGB and checks if numbers are below 256 */
int	check_rgb_format(char *str, t_game *game, char c)
{
	char	**rgb;

	rgb = ft_split(str, ',');
	if (!rgb)
		return (1);
	if (check_rgb_number(rgb))
		return (free_array(rgb), 1);
	if (c == 'f')
		add_values(rgb, 'f', game);
	else
		add_values(rgb, 'c', game);
	if ((game->texture.floor[0] > 255) || (game->texture.ceiling[0] > 255))
		return (free_array(rgb), 1);
	if ((game->texture.floor[1] > 255) || (game->texture.ceiling[1] > 255))
		return (free_array(rgb), 1);
	if ((game->texture.floor[2] > 255) || (game->texture.ceiling[2] > 255))
		return (free_array(rgb), 1);
	free_array(rgb);
	return (0);
}

/* Gets RGB from map->config and returns error if invalid */
int	check_colors(t_map *map, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (map->config[i])
	{
		j = 0;
		while (map->config[i][j])
		{
			if (map->config[i][j] == 'F'
				&& check_rgb_format(&map->config[i][j + 2], game, 'f'))
				return (printf("Error\nInvalid RGB value\n"), 1);
			else if (map->config[i][j] == 'C'
				&& check_rgb_format(&map->config[i][j + 2], game, 'c'))
				return (printf("Error\nInvalid RGB value\n"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_atol_rgb(char *nptr)
{
	long	res;
	int		neg;

	res = 0;
	neg = 1;
	if (!nptr)
		return (0);
	while ((*nptr == 32) || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			neg = -neg;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (res > (INT_MAX - (*nptr - '0')) / 10)
			return (256);
		res = res * 10 + (*nptr - '0');
		nptr++;
	}
	return (res * neg);
}
