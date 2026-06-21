/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 09:11:07 by mefische          #+#    #+#             */
/*   Updated: 2026/06/19 17:22:44 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* Calculates the perpendicular distance from the player to the wall
	after the DDA loop. One delta is subtracted because the last DDA
	step already moved the ray into the wall cell.
	- We subtract 1 delta because in the loop we stepped 
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

/* Converts perpendicular wall distance into the wall slice height
	on screen. Smaller distance means a taller wall. The wall is then
	vertically centered in the window by computing the start and end
	draw positions. Remember that in MLX, smaller y values go upward,
	which is why draw_start uses subtraction from the screen center. */
void	wall_height(t_game *game, t_ray *ray)
{
	ray->line_height = (int)((game->win_height / ray->p_dist) * 1.8);
	ray->draw_start = -ray->line_height / 2 + game->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + game->win_height / 2;
	if (ray->draw_end >= game->win_height)
		ray->draw_end = game->win_height - 1;
}

/* Resets the ray fields before a new ray is prepared and cast.
	This avoids keeping values from the previous screen column. */
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

/* Sets up one ray for the current screen column.
	- The player's position is used as the ray origin, and camera_x maps 
	the column index to the camera plane range from -1 to 1.
	- The ray direction is then calculated from player direction plus
	camera plane offset.
	- Camera plane represents the width/angle view of the player
	- Delta distances store how much distance is needed to cross one
	grid line on each axis.
	- Remember that 1.0 is used to force double division, and when a ray
	direction is zero, a very large value is used to avoid division by zero. */
void	setup_ray(t_game *game, int i)
{
	double	camera_x;

	camera_x = 2.0 * i / (double)game->win_width - 1.0;
	game->ray.map_x = (int)game->player.x;
	game->ray.map_y = (int)game->player.y;
	game->ray.pos_x = game->player.x;
	game->ray.pos_y = game->player.y;
	game->ray.dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	game->ray.dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	if (game->ray.dir_x == 0)
		game->ray.delta_x = 1e30;
	else
		game->ray.delta_x = fabs(1.0 / game->ray.dir_x);
	if (game->ray.dir_y == 0)
		game->ray.delta_y = 1e30;
	else
		game->ray.delta_y = fabs(1.0 / game->ray.dir_y);
	ray_reset(game);
}
