#ifndef CUB3D_H
#define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
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
	char	**design;
	char	**config;
	int		width;
	int		height;
	char	orient;
	int		start;
}			t_map;

typedef struct s_textures
{
	void	*n_wall;
	void	*s_wall;
	void	*e_wall;
	void	*w_wall;
	int		floor;
	int		ceiling;
}			t_textures;

typedef struct s_player
{
	int			x;
	int			y;
	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		key_right;

}			t_player;

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
}			t_game;

//Probably a struct t_ray for raycasting

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
void 	id_count(char id, int *counter);
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


// INITIALIZATION
t_game	init_game_data(void);
void	init_player(t_player *player);
void	init_game(t_game *game);

// PUT PIXELS
void	put_pixel(int x, int y, int color, t_game *game);
void	draw_square(int x, int y, int size, int color, t_game *game);
int		draw_loop(t_game *game);
void	clear_image(t_game *game);
void	draw_map(t_game *game);

//PLAYER MOVEMENT
int		move_player(t_player *player);

// KEY EVENTS
int		key_press(int keysym, t_game *game);
int		key_release(int keysym, t_game *game);

// FREE DATA
int		close_window(void *param);
void	free_array(char **array);
void	free_data(t_game *game);
void	free_map(t_map *map);

#endif