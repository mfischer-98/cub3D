/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:17:17 by mefische          #+#    #+#             */
/*   Updated: 2026/06/12 14:53:14 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* Function for when player releases a move key */
int	key_release(int keysym, t_game *game)
{
	if (keysym == W)
		game->player.key_up = false;
	if (keysym == S)
		game->player.key_down = false;
	if (keysym == A)
		game->player.key_left = false;
	if (keysym == D)
		game->player.key_right = false;
	if (keysym == XK_Right)
		game->player.right_rotate = false;
	if (keysym == XK_Left)
		game->player.left_rotate = false;
	return (0);
}

/* Function for when player presses a key */
int	key_press(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		close_window(game);
	if (keysym == W)
		game->player.key_up = true;
	if (keysym == S)
		game->player.key_down = true;
	if (keysym == A)
		game->player.key_left = true;
	if (keysym == D)
		game->player.key_right = true;
	if (keysym == XK_Right)
		game->player.right_rotate = true;
	if (keysym == XK_Left)
		game->player.left_rotate = true;
	return (0);
}

/* Before closing the window it frees all data */
int	close_window(t_game *game)
{
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	free_texture(game, &game->texture.n_wall);
	free_texture(game, &game->texture.s_wall);
	free_texture(game, &game->texture.w_wall);
	free_texture(game, &game->texture.e_wall);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_data(game);
	exit(1);
}
