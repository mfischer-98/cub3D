/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 15:10:59 by mefische          #+#    #+#             */
/*   Updated: 2026/06/05 11:23:31 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "libft/libft.h"
# include "mlx/mlx.h"
# include <X11/keysym.h>

# define TEXT_SIZE 32 //64x64? ou 32x32?

# define W 119
# define A 97
# define S 115
# define D 100
# define PI 3.14159265359

typedef struct s_map
{
	char		**design;
	char		**config;
	int			width;
	int			height;
	char		orient;
	int			start;
}			t_map;

typedef struct s_textures
{
	void		*n_wall;
	void		*s_wall;
	void		*e_wall;
	void		*w_wall;
	int			floor;
	int			ceiling;
}			t_textures;

typedef struct s_player
{
	double		x;
	double		y;
	double		angle;

	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		key_right;
	bool		left_rotate;
	bool		right_rotate;

}			t_player;

typedef struct s_ray
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;

	int		map_x;
	int		map_y;

	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;

	int		hit; //flags pra saber se bateu na parede e qual lado
	int		side;

	double	p_dist; // perpendicular distance
	int		line_height;
	int		draw_start;
	int		draw_end;
}			t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	void		*img;
	t_map		map;
	t_player	player;
	t_textures	texture;
	t_ray		ray;
}			t_game;

// PARSING
int		parsing(int ac, char **args, t_game *game);
int		check_number(int n);
int		check_fd(char *file_name, char c);
int		check_map_name(char *name);
int		not_identifier(char *line);
int		skip_spaces(char *str, int i);
int		check_textures(t_map *map);
int		read_config(char *map_file, t_map *map);
int		get_line(t_map *map, char *line, int *count);
int		check_duplicates(t_map *map);
void	id_count(char id, int *counter);
int		check_colors(t_map *map);
int		check_rgb_format(char *str);
int		check_rgb_number(char **str);
void	read_map(char *map_file, t_map *map);
void	get_map_design(t_map *map, char *line, int fd);
int		map_height(int start, char *map_file);
int		map_start(char *map_file);
void	line_trim(char *str);
int		line_len(char *str);
char	*convert_tabs(char *str);
void	find_player(t_map *map, t_player *player);
char	**copy_array(t_map *map);
int		flood_fill(t_map *map, char **map_copy, int x, int y);
int		check_walls(t_map *map, t_player *player);
void	run_file(char *line, int fd);

// INITIALIZATION
t_game	init_game_data(void);
void	init_player(t_player *player);
void	init_game(t_game *game);
void	get_player_angle(t_game *game);
void	init_ray(t_ray *ray);

// PUT PIXELS
void	put_pixel(int x, int y, int color, t_game *game);
void	draw_square(int x, int y, int size, int color, t_game *game);
int		render_scene(t_game *game);
void	clear_image(t_game *game);
void	draw_map(t_game *game);

// DDA RAYCASTING
void	DDA_grid_step(t_game *game, t_ray *ray);
void	DDA_ray_loop(t_game *game, t_ray *ray, int step_x, int step_y);
void	ray_line(double angle, int i, t_game *game);
void	perpend_dist(t_ray *ray);
void	wall_height(t_game *game, t_ray *ray);
void	ray_reset(t_game *game);
void	setup_ray(t_game *game, double angle);
void	draw_wall_column(int x, t_game *game, t_ray *ray);

// PLAYER MOVEMENT
double	rotate_player(t_player *player);
int		move_player(t_player *player, t_map *map);
void	move_vertical(t_player *player, t_map *map, double speed);
void	move_horizontal(t_player *player, t_map *map, double speed);

// KEY EVENTS
int		key_press(int keysym, t_game *game);
int		key_release(int keysym, t_game *game);

// RAY
int		touch(double px, double py, t_game *game);
void	ray_line(double angle, int i, t_game *game);

// FREE DATA
int		close_window(t_game *game);
void	free_array(char **array);
void	free_data(t_game *game);
void	free_map(t_map *map);

#endif