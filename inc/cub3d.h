#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
# include "mlx/mlx.h"
# include <X11/keysym.h>

# define WIN_W 1280
# define WIN_H 720
# define TEXT_SIZE 64 //64x64? ou 32x32?

typedef struct s_map
{
	char	**design;
	char	**config;
	int		width;
	int		height;
	char	orient;
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
	int			pos_x;
	int			pos_y;
}			t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
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
int		is_identifier(char *line);
int		check_textures(t_map *map);
int		read_config(char *map_file, t_map *map);
int		get_line(t_map *map, char *line, int *count);
int		check_duplicates(t_map *map);
void 	id_count(char id, int *counter);
int		check_colors(t_map *map);
int		check_rgb_format(char *str);
int		check_rgb_number(char **str);



// INITIALIZATION
t_game	init_game(void);

// WINDOW EVENTS
int		close_window(void *param);
int		handle_input(int keysym, void *param);

// FREE DATA
void	free_array(char **array);


#endif