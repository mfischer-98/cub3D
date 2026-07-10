/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntomas-g <ntomas-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 14:43:20 by mefische          #+#    #+#             */
/*   Updated: 2026/07/10 11:29:00 by ntomas-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* Starts mlx and creates a window */
void	init_game(t_game *game)
{
	game->win_width = 1920;
	game->win_height = 1080;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->win_width,
			game->win_height, "cub3D");
	if (!game->win)
		return (close_window(game), (void)1);
	game->img = mlx_new_image(game->mlx, game->win_width,
			game->win_height);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argc;
	(void)argv;
	game = init_game_data();
	if (parsing(argc, argv, &game))
	{
		free_data(&game);
		return (1);
	}
	get_player_angle(&game);
	init_game(&game);
	load_textures(&game);
	mlx_hook(game.win, 17, 0, &close_window, &game);
	mlx_hook(game.win, 2, 1L << 0, &key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, &key_release, &game);
	mlx_hook(game.win, 6, 1L << 6, &mouse_move, &game);
	mlx_mouse_move(game.mlx, game.win, game.win_width / 2, game.win_height / 2);
	mlx_loop_hook(game.mlx, &render_scene, &game);
	mlx_loop(game.mlx);
	return (0);
}
//mlx_mouse_hide(game.mlx, game.win);
