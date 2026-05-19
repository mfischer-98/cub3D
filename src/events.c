/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:17:17 by mefische          #+#    #+#             */
/*   Updated: 2026/05/19 15:38:49 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	close_window(void *param)
{
	t_game *game;

	game = (t_game *)param;
	//free_images(game);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	//free_data(game);
	exit(1);
}

int	handle_input(int keysym, void *param)
{
	t_game *game;

	game = (t_game *)param;
	if (keysym == XK_Escape)
		close_window(game);
	return (0);
}