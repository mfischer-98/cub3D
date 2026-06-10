/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@openai.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 16:40:00 by copilot           #+#    #+#             */
/*   Updated: 2026/06/10 16:40:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	apply_fog(int color, double dist, double fog_start, double fog_end)
{
	double	f;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if (dist <= fog_start)
		return (color);
	if (dist >= fog_end)
		return (0);
	f = (dist - fog_start) / (fog_end - fog_start);
	if (f < 0)
		f = 0;
	if (f > 1)
		f = 1;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = (unsigned int)(r * (1.0 - f));
	g = (unsigned int)(g * (1.0 - f));
	b = (unsigned int)(b * (1.0 - f));
	return ((r << 16) | (g << 8) | b);
}

int	apply_fog_row(int color, int y, int height)
{
	double	factor;
	double	dist;
	int	center;

	center = height / 2;
	factor = fabs((double)y - (double)center) / (double)center;
	dist = BORDER_FOG_FAR - factor * (BORDER_FOG_FAR - BORDER_FOG_NEAR);
	return (apply_fog(color, dist, BORDER_FOG_START, BORDER_FOG_END));
}
