/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 09:09:27 by mefische          #+#    #+#             */
/*   Updated: 2026/06/05 11:40:14 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* Decides which direction the ray goes and calculates the distance
	until the first horizontal or verticla line */
void	DDA_grid_step(t_game *game, t_ray *ray)
{
	int	step_x;
	int	step_y;

	if (ray->dir_x < 0)
	{
		step_x = -1;
		ray->side_x = (ray->pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		step_y = -1;
		ray->side_y = (ray->pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_y;
	}
	DDA_ray_loop(game, ray, step_x, step_y);
}

void	DDA_ray_loop(t_game *game, t_ray *ray, int step_x, int step_y)
{
	ray->hit = 0;
	ray->side = 0;

	while (ray->hit == 0)
	{
		// Linha y (VERTICAL) está mais perto
		if (ray->side_x < ray->side_y)
		{
			//avanço a distancia para prox linha vertical
			ray->side_x += ray->delta_x;
			//avanca grid no mapa
			ray->map_x += step_x;
			//marca que estamos no lado X, que é vertical
			ray->side = 0;
		}
		// Linha x (HORIZONTAL) está mais perto
		else
		{
			//avanço a distancia para prox linha horizontal
			ray->side_y += ray->delta_y;
			//avanca grid no mapa
			ray->map_y += step_y;
			//marca que estamos no lado Y, que é horizontal
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_y >= game->map.height
			|| ray->map_x < 0 || ray->map_x >= game->map.width)
			break ;
		if (game->map.design[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	ray_line(double angle, int i, t_game *game)
{
	setup_ray(game, angle);
	DDA_grid_step(game, &game->ray);
	perpend_dist(&game->ray);
	wall_height(game, &game->ray);
	draw_wall_column(i, game, &game->ray);
}
