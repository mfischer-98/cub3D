/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 09:09:27 by mefische          #+#    #+#             */
/*   Updated: 2026/07/14 13:32:43 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

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

/* Advances the ray through the map grid using DDA until it hits
	a wall or goes out of bounds. 
	- side_x < side_y = vertical line is closer
	- It checks whether the next step crosses a vertical (side = 0 = X)
		or horizontal (side = 1 = Y) grid line first. */
void	dda_ray_loop(t_game *game, t_ray *ray, int step_x, int step_y)
{
	ray->hit = 0;
	ray->side = 0;
	while (ray->hit == 0)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += step_y;
			ray->side = 1;
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

/* Determines which face of the wall was hit based on the ray
	direction and whether the collision happened on a vertical
	or horizontal side. */
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

/* Sets up the ray for one screen column, runs the DDA collision
	check, calculates the perpendicular wall distance, computes
	the wall height, and draws the wall slice. */
void	ray_line(int i, t_game *game)
{
	setup_ray(game, i);
	dda_grid_step(game, &game->ray);
	perpend_dist(&game->ray);
	wall_height(game, &game->ray);
	draw_wall_column(i, game, &game->ray);
}
