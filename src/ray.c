/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 09:09:27 by mefische          #+#    #+#             */
/*   Updated: 2026/06/15 16:35:46 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* Decides which direction the ray goes and calculates the distance
	until the first horizontal or verticla line */
void	dda_grid_step(t_game *game, t_ray *ray)
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
	dda_ray_loop(game, ray, step_x, step_y);
}

void	dda_ray_loop(t_game *game, t_ray *ray, int step_x, int step_y)
{
	ray->hit = 0;
	ray->side = 0;
	while (ray->hit == 0)
	{
		if (ray->side_x < ray->side_y) // Linha y (VERTICAL) está mais perto
		{
			ray->side_x += ray->delta_x; //avanço a distancia para prox linha vertical
			ray->map_x += step_x; //avanca grid no mapa
			ray->side = 0; //marca que estamos no lado X, que é vertical
		}
		else // Linha x (HORIZONTAL) está mais perto
		{
			ray->side_y += ray->delta_y; //avanço a distancia para prox linha horizontal
			ray->map_y += step_y; //avanca grid no mapa
			ray->side = 1; //marca que estamos no lado Y, que é horizontal
		}
		if (ray->map_y < 0 || ray->map_y >= game->map.height
			|| ray->map_x < 0 || ray->map_x >= game->map.width)
			break ;
		if (game->map.design[ray->map_y][ray->map_x] == '1')
		{
			get_wall_face(step_x, step_y, ray);
			ray->hit = 1;
		}
	}
}

void	get_wall_face(int step_x, int step_y, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (step_x > 0)
			ray->wall_face = 'W';
		else
			ray->wall_face = 'E';
	}
	else
	{
		if (step_y > 0)
			ray->wall_face = 'N';
		else
			ray->wall_face = 'S';
	}
}

void	ray_line(int i, t_game *game)
{
	setup_ray(game, i);
	dda_grid_step(game, &game->ray);
	perpend_dist(&game->ray);
	wall_height(game, &game->ray);
	draw_wall_column(i, game, &game->ray);
}
