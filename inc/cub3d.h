/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 15:10:59 by mefische          #+#    #+#             */
/*   Updated: 2026/07/15 01:53:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <X11/keysym.h>

# define SPEED 0.1
# define ANGLE_SPEED 0.1

# define W 119
# define A 97
# define S 115
# define D 100
# define F 102
# define PI 3.14159265359
# define WALL_FOG_START 1.0
# define WALL_FOG_END 3.0
# define BORDER_FOG_START 0.25
# define BORDER_FOG_END 0.4
# define BORDER_FOG_NEAR 0.2
# define BORDER_FOG_FAR 0.5

typedef struct s_map
{
	char		**design;
	char		**config;
	int			width;
	int			height;
	char		orient;
	int			start;
}			t_map;

typedef struct s_img
{
	void	*img;
	char	*buffer;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_textures
{
	t_img		n_wall;
	t_img		s_wall;
	t_img		e_wall;
	t_img		w_wall;
	int			hex_floor;
	int			hex_ceiling;
	int			floor[3];
	int			ceiling[3];
}			t_textures;

typedef struct s_player
{
	double		x;
	double		y;
	double		angle;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
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

	int		hit;
	int		side;
	char	wall_face;

	double	p_dist;
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
	bool		fog_enabled;
	t_textures	texture;
	t_ray		ray;
}			t_game;

// PARSING
int		parsing(int ac, char **args, t_game *game);
int		check_number(int n);
int		check_fd(char *file_name, char c);
int		check_map_name(char *name);
char	**read_file(char *file);
int		count_lines(char *file);
int		not_identifier(char *line);
int		skip_spaces(char *str, int i);
int		check_textures(char **map_file, t_game *game, t_map *map);
int		read_config(char **map_file, t_map *map);
int		check_duplicates(t_map *map);
void	id_count(char id, int *counter);
int		check_colors(t_map *map, t_game *game);
int		check_rgb_format(char *str, t_game *game, char c);
int		check_rgb_number(char **str);
int		read_map(char **map_file, t_map *map);
int		map_height(int start, char **map_file);
int		map_start(char **map_file);
char	*convert_tabs(char *str);
void	find_player(t_map *map, t_player *player);
char	**copy_array(t_map *map);
int		flood_fill(t_map *map, char **map_copy, int x, int y);
int		check_walls(t_map *map, t_player *player);

// INITIALIZATION
t_game	init_game_data(void);
void	init_player(t_player *player);
void	init_game(t_game *game);
void	init_textures(t_textures *text);
void	get_player_angle(t_game *game);
void	init_ray(t_ray *ray);

// PUT PIXELS
void	put_pixel(int x, int y, int color, t_game *game);
int		apply_fog(int color, double dist, double fog_start, double fog_end);
int		apply_fog_row(int color, int y, int height);
int		render_scene(t_game *game);
void	clear_image(t_game *game);

// TEXTURES
void	load_textures(t_game *game);
char	*get_wall_path(t_game *game, char c);
void	get_buffers(t_textures *textures);
t_img	*get_face_texture(char face, t_game *game);
int		get_texture_color(t_img *text, int text_x, int text_y);
int		render_walls(int x, int y, t_game *game, t_ray *ray);
int		convert_rgb(int *rgb);

// DDA RAYCASTING
void	dda_grid_step(t_game *game, t_ray *ray);
void	dda_ray_loop(t_game *game, t_ray *ray, int step_x, int step_y);
void	perpend_dist(t_ray *ray);
void	wall_height(t_game *game, t_ray *ray);
void	ray_reset(t_game *game);
void	setup_ray(t_game *game, int i);
void	draw_wall_column(int x, t_game *game, t_ray *ray);
int		touch(double px, double py, t_game *game);
void	ray_line(int i, t_game *game);
void	get_wall_face(int step_x, int step_y, t_ray *ray);

// PLAYER MOVEMENT
double	rotate_player(t_player *player);
int		move_player(t_player *player, t_map *map);
void	move_vertical(t_player *player, t_map *map);
void	move_horizontal(t_player *player, t_map *map);
int		not_wall(t_map *map, double x, double y);

// KEY EVENTS
int		key_press(int keysym, t_game *game);
int		key_release(int keysym, t_game *game);

// FREE DATA
int		close_window(t_game *game);
void	free_array(char **array);
void	free_data(t_game *game);
void	free_map(t_map *map);
void	free_texture(t_game *game, t_img *img);

#endif