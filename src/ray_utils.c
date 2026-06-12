/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 09:11:07 by mefische          #+#    #+#             */
/*   Updated: 2026/06/12 15:11:53 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* Get wall distance after DDA loop 
	- we subtract 1 delta because in the loop we stepped 
	once into the wall */
void	perpend_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->p_dist = ray->side_x - ray->delta_x;
	else
		ray->p_dist = ray->side_y - ray->delta_y;
	if (ray->p_dist < 0.001)
		ray->p_dist = 0.001;
}

/* Convert wall distance into wall height 
	- smaller distance = bigger wall */
void	wall_height(t_game *game, t_ray *ray)
{
	// Quanto menos a distancia (pdist), maior a parede
	ray->line_height = (int)(game->win_height / ray->p_dist);
	// Draw_start: center of line + center of window
	// Remember in MLX y decreases as it goes up so -
	ray->draw_start = -ray->line_height / 2 + game->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + game->win_height / 2;
	if (ray->draw_end >= game->win_height)
		ray->draw_end = game->win_height - 1;
}

void	ray_reset(t_game *game)
{
	game->ray.side_x = 0;
	game->ray.side_y = 0;
	game->ray.hit = 0;
	game->ray.side = 0;
	game->ray.wall_face = 0;
	game->ray.p_dist = 0;
	game->ray.line_height = 0;
	game->ray.draw_start = 0;
	game->ray.draw_end = 0;
}

void	setup_ray(t_game *game, int i)
{
	double	camera_x;

	camera_x = 2.0 * i / (double)game->win_width - 1.0;
	
	/* PLayer position = ray origin */
	game->ray.map_x = (int)game->player.x;
	game->ray.map_y = (int)game->player.y;
	
	/* Ray direction */
	game->ray.pos_x = game->player.x;
	game->ray.pos_y = game->player.y;

	/* Ray direction */
	game->ray.dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	game->ray.dir_y = game->player.dir_y + game->player.plane_y * camera_x;

	/* Distance needed to cross one grid line on x */
	if (game->ray.dir_x == 0)
		game->ray.delta_x = 1e30;
	else
		game->ray.delta_x = fabs(1.0 / game->ray.dir_x); // 1.0 pq queremos valor double
	
	/* Distance needed to cross one grid line on y */
	if (game->ray.dir_y == 0)
		game->ray.delta_y = 1e30;
	else
		game->ray.delta_y = fabs(1.0 / game->ray.dir_y);
	ray_reset(game);
}
