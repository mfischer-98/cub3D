/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 08:35:08 by mefische          #+#    #+#             */
/*   Updated: 2026/07/14 13:32:43 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

char	*get_wall_path(t_game *game, char c)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.config[i])
	{
		j = 0;
		j = skip_spaces(game->map.config[i], j);
		if (game->map.config[i][j] == c)
		{
			j += 2;
			j = skip_spaces(game->map.config[i], j);
			return (&game->map.config[i][j]);
		}
		i++;
	}
	return (NULL);
}

int	convert_rgb(int *rgb)
{
	int		i;
	int		res;

	res = 0;
	i = 0;
	while (i < 3)
	{
		res = (res << 8) + rgb[i];
		i++;
	}
	return (res);
}

void	get_buffers(t_textures *textures)
{
	textures->n_wall.buffer = mlx_get_data_addr(textures->n_wall.img,
			&textures->n_wall.bpp, &textures->n_wall.line_length,
			&textures->n_wall.endian);
	textures->s_wall.buffer = mlx_get_data_addr(textures->s_wall.img,
			&textures->s_wall.bpp, &textures->s_wall.line_length,
			&textures->s_wall.endian);
	textures->e_wall.buffer = mlx_get_data_addr(textures->e_wall.img,
			&textures->e_wall.bpp, &textures->e_wall.line_length,
			&textures->e_wall.endian);
	textures->w_wall.buffer = mlx_get_data_addr(textures->w_wall.img,
			&textures->w_wall.bpp, &textures->w_wall.line_length,
			&textures->w_wall.endian);
}

void	load_textures(t_game *game)
{
	game->texture.n_wall.img = mlx_xpm_file_to_image
		(game->mlx, get_wall_path(game, 'N'),
			&game->texture.n_wall.width, &game->texture.n_wall.height);
	game->texture.s_wall.img = mlx_xpm_file_to_image
		(game->mlx, get_wall_path(game, 'S'),
			&game->texture.s_wall.width, &game->texture.s_wall.height);
	game->texture.e_wall.img = mlx_xpm_file_to_image
		(game->mlx, get_wall_path(game, 'E'),
			&game->texture.e_wall.width, &game->texture.e_wall.height);
	game->texture.w_wall.img = mlx_xpm_file_to_image
		(game->mlx, get_wall_path(game, 'W'),
			&game->texture.w_wall.width, &game->texture.w_wall.height);
	get_buffers(&game->texture);
	game->texture.hex_floor = convert_rgb(game->texture.floor);
	game->texture.hex_ceiling = convert_rgb(game->texture.ceiling);
}
