/* ************************************************************************** */
/*		                                                                      */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 08:35:08 by mefische          #+#    #+#             */
/*   Updated: 2026/06/09 11:08:39 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* Chooses correct wall texture */
t_img	*get_face_texture(char face, t_game *game)
{
	if (face == 'N')
		return (&game->texture.n_wall);
	else if (face == 'S')
		return (&game->texture.s_wall);
	else if (face == 'W')
		return (&game->texture.w_wall);
	else if (face == 'E')
		return (&game->texture.e_wall);
	return (NULL);
}

/* Returns the color of one pixel inside a texture image.
	text_x and text_y are the coordinates inside the texture,
	and the function uses the texture buffer, line length and bpp
	to find the exact memory address of that pixel. */
int	get_texture_color(t_img *text, int text_x, int text_y)
{
	char	*pixel;
	int		color;

	if (text_x < 0)
		text_x = 0;
	if (text_x >= text->width)
		text_x = text->width - 1;
	if (text_y < 0)
		text_y = 0;
	if (text_y >= text->height)
		text_y = text->height - 1;
	pixel = text->buffer + ((text_y * text->line_length)
			+ (text_x * (text->bpp / 8)));
	color = *(int *)pixel;
	return (color);
}

/* Computes the horizontal texture coordinate (text_x) for this wall slice.
	It finds the exact point where the ray hit the wall, keeps only the
	fractional part inside the tile, converts that into a texture column */
int	get_text_x(t_img *text, t_ray *ray)
{
	double	wall_x;
	int		text_x;

	if (ray->side == 0)
		wall_x = ray->pos_y + ray->p_dist * ray->dir_y;
	else
		wall_x = ray->pos_x + ray->p_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	text_x = (int)(wall_x * (double)text->width);
	if (text_x < 0)
		text_x = 0;
	if (text_x >= text->width)
		text_x = text->width - 1;
	return (text_x);
}

/* 	First it selects the correct wall texture, then gets the texture column
	that matches the wall hit point, and finally stretches that texture
	vertically between draw_start and draw_end by sampling texture pixels
	from top to bottom and writing them to the screen. */
static int	draw_wall_pixels(int x, int y, t_game *game, t_ray *ray)
{
	t_img	*text;
	double	step;
	double	text_pos;
	int		text_x;
	int		color;

	text = get_face_texture(ray->wall_face, game);
	text_x = get_text_x(text, ray);
	step = 1.0 * text->height / ray->line_height;
	text_pos = (ray->draw_start - game->win_height / 2
			+ ray->line_height / 2) * step;
	while (y <= ray->draw_end)
	{
		color = get_texture_color(text, text_x, (int)text_pos);
		if (game->fog_enabled)
			color = apply_fog(color, ray->p_dist,
					WALL_FOG_START, WALL_FOG_END);
		put_pixel(x, y++, color, game);
		text_pos += step;
	}
	return (y);
}

/* Draws the textured wall stripe for one screen column x */
int	render_walls(int x, int y, t_game *game, t_ray *ray)
{
	if (ray->line_height <= 0)
		return (y);
	return (draw_wall_pixels(x, y, game, ray));
}
