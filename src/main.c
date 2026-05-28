/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 14:43:20 by mefische          #+#    #+#             */
/*   Updated: 2026/05/28 11:07:48 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argc;
	(void)argv;
	game = init_game();
	if (parsing(argc, argv, &game))
	{
		free_data(&game);
		return (1);
	}
	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);
	game.win = mlx_new_window(game.mlx, WIN_W, WIN_H, "cub3D"); //later map.width and height
	if (!game.win)
		return (close_window(&game), 1);
	mlx_hook(game.win, 17, 0, &close_window, &game); //X working
	mlx_key_hook(game.win, &handle_input, &game);
	mlx_loop(game.mlx);
	free_data(&game);
	return (0);
}