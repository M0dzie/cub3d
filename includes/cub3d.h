/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:20:01 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/07/24 20:03:34 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef CUB3D_H
// # define CUB3D_H
// # include "libft/includes/libft.h"
// # include "mlx_linux/mlx.h"
// # include <stdio.h>
// # include <math.h>

// # define WIN_WIDTH 1980.0
// # define WIN_HEIGHT 1080.0

// # define SPEED_PLAYER 0.015
// # define SPEED_ANGLE 0.01

// # define TRUE 1
// # define FALSE 0

// # ifndef KEYS
// #  if __linux__
// #   define ESC 65307
// #   define W 119
// #   define A 97
// #   define S 115
// #   define D 100
// #   define M 109
// #   define L_ARROW 65361
// #   define R_ARROW 65363
// #  elif __APPLE__
// #   define ESC 53
// #   define W 13
// #   define A 0
// #   define S 1
// #   define D 2
// #   define M 46
// #   define L_ARROW 123
// #   define R_ARROW 124
// #  endif
// # endif

// typedef struct s_vector
// {
// 	double	x;
// 	double	y;
// }			t_vector;

// typedef struct s_data
// {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }			t_data;

// typedef struct s_map
// {
// 	int		map_x;
// 	int		map_y;
// 	int		width;
// 	int		height;
// 	char	**array;
// }			t_map;

typedef struct s_tex_data
{
	int		tex_x;
	int		tex_y;
	int		color;
	double	tex_pos;
	double	step;
}			t_tex_data;

// typedef struct s_ray
// {
// 	int				side;
// 	int				wall_height;
// 	double			coef;
// 	double			dist;
// 	t_vector		axis;
// 	t_vector		dist_next_inter;
// 	t_vector		next_inter;
// 	t_tex_data		tex;
// }					t_ray;

// typedef struct s_player
// {
// 	t_vector	axis;
// 	t_vector	axis_side;
// 	t_vector	fov;
// 	t_vector	pos;
// 	t_ray		**ray;
// }				t_player;

typedef struct s_xpm
{
	int		fd;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		*data;
	char	*path;
	void	*tex;
	int		*px;
}			t_xpm;

// typedef struct s_key
// {
// 	int		w;
// 	int		s;
// 	int		a;
// 	int		d;
// 	int		r_arrow;
// 	int		l_arrow;
// }			t_key;

// typedef struct s_cub
// {
// 	int				floor;
// 	int				roof;
// 	int				*rgb_floor;
// 	int				*rgb_roof;
// 	char			*file;
// 	char			**file_split;
// 	void			*mlx;
// 	void			*win;
// 	double			cos_angle;
// 	double			sin_angle;
// 	t_xpm			north;
// 	t_xpm			south;
// 	t_xpm			west;
// 	t_xpm			east;
// 	t_data			game;
// 	t_key			key;
// 	struct s_map	*map;
// 	struct s_player	*p;
// }					t_cub;

// int		are_rgb_valid(t_cub *cub);
// int		check_border(t_cub *cub);
// int		display_error(char *name, int num_error);
// int		display_error_texture(t_cub *cub);
// int		exit_cub(t_cub *cub, int xpm);
// int		init_color(t_cub *cub);
// int		init_file(t_cub *cub, char *file_name);
// int		init_map(t_cub *cub, char **argv);
// int		init_mlx(t_cub *cub);
// int		init_player(t_cub *cub);
// int		init_texture(t_cub *cub);
// int		is_valid_number(char *rgb);
// int		parsing_map(t_cub *cub, char **argv);
// int		parse_xpm(t_cub *cub);
// int		put_pixel(t_data *data, int x, int y, int color);
// int		render_cub3d(t_cub *cub);

// void	init_raycasting(t_cub *cub);
// void	move_player(t_cub *cub, t_vector coef, int sign);
// void	render_texture(t_cub *cub);
// void	rotate_player(t_cub *cub, int sign);
// void	save_texture(int *fd, char *path, char **path_save);

// #endif

#ifndef CUB3D_H
# define CUB3D_H
# include "libft/includes/libft.h"
# include "mlx_linux/mlx.h"
# include <stdio.h>
# include <math.h>

# ifndef GRID_MINI
#  define GRID_MINI 256
// #  define GRID_MINI 128
# endif

# ifndef GRID_MAP
#  define GRID_MAP 100
# endif

// # define WIN_WIDTH 1980.0
// # define WIN_HEIGHT 1080.0
# define WIN_WIDTH 1280.0
# define WIN_HEIGHT 720.0

# define SPEED_MINI 14.0
# define SPEED_ANGLE 2.0
// # define SPEED_MINI 0.1
// # define SPEED_ANGLE 0.05

# define FOV 66.0

# define TRUE 1
# define FALSE 0

# ifndef COLORS
#  define WALL_COLOR 0x00202020
// #  define NORTH 1
// #  define SOUTH 2
// #  define EAST 3
// #  define WEST 4
#  define NORTH 0x000362fc
#  define SOUTH 0x00fc0367
#  define WEST 0x0000ff3c
#  define EAST 0x00ffe600
#  define ANGLE 0x0000ffb7
# endif

# ifndef KEYS
#  if __linux__
#   define ESC 65307
#   define W 119
#   define A 97
#   define S 115
#   define D 100
#   define M 109



#   define TEST 112




#   define L_ARROW 65361
#   define R_ARROW 65363
#  elif __APPLE__
#   define TEST 112
#   define ESC 53
#   define W 13
#   define A 0
#   define S 1
#   define D 2
#   define M 46
#   define L_ARROW 123
#   define R_ARROW 124
#  endif
# endif

typedef struct s_vector
{
	double	x;
	double	y;
}			t_vector;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
}			t_mlx;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_map
{
	char	**array;
	int		width;
	int		height;

	// tests
	int		min_x;
	int		min_y;
	int		max_x;
	int		max_y;
}			t_map;

typedef struct s_dist
{
	int	n;
	int	s;
	int	w;
	int	e;
	int	nw;
	int	se;
	int	ne;
	int	sw;
}		t_dist;

// typedef struct s_ray
// {
// 	int				side;
// 	int				wall_height;
// 	double			coef;
// 	double			dist;
// 	t_vector		axis;
// 	t_vector		dist_next_inter;
// 	t_vector		next_inter;
// 	t_tex_data		tex;
// }					t_ray;

typedef struct s_ray_map
{
	t_vector		coef_ns;
	t_vector		wall;
	// t_vector	coef_we;
	// t_vector	start;
	// double		dist;
	double			angle;
	unsigned int	side;
	t_tex_data	tex;

	double		distance;
	double		wall_height;
	double		margin;
	// int			map_x;
	// int			map_y;
	// t_vector	coord_wall;
	t_vector	map;
	int			index_wall;
}				t_ray_map;

typedef struct s_ray
{
	t_vector	coef_ns;
	t_vector	coef_we;
	t_vector	coef_nwse;
	t_vector	coef_nesw;
	t_vector	start;
	t_dist		dist;
	// int			angle;
	double		angle;
	
}				t_ray;

typedef struct s_wall
{
	int		width;
	double	percent_start;
	double	percent_end;
	int		side;
}					t_wall;

typedef struct s_player
{
	t_ray_map	**ray;
	t_ray		pos;
	double		coef;
	int			nb_wall;
	t_wall		*wall;
}				t_player;

typedef struct s_imgs
{
	int		show_mini;
	t_data	minimap;
	t_data	back;
	t_data	p;
}			t_imgs;

typedef struct s_key
{
	int		w;
	int		s;
	int		a;
	int		d;



	int		test;




	int		r_arrow;
	int		l_arrow;
}			t_key;

typedef struct s_cub
{
	// fds textures, found if better to use fd int or string as path
	int	fd_north;
	int	fd_south;
	int	fd_west;
	int	fd_east;

	int				floor;
	int				roof;
	int 			*rgb_floor;
	int 			*rgb_roof;
	char			*file;
	char			**file_split;
	void			*mlx;
	void			*win;
	t_imgs			*imgs;
	t_key			key;
	struct s_map	*map;
	struct s_player	*p;

	t_xpm			north;
	t_xpm			south;
	t_xpm			west;
	t_xpm			east;
	t_data			game;
}					t_cub;

int		are_rgb_valid(t_cub *cub);
int		calcul_coef(t_cub *cub);
int		check_border(t_cub *cub);
int		display_error(char *name, int num_error);
int		display_error_texture(t_cub *cub);
int		init_color(t_cub *cub);
int		init_file(t_cub *cub, char *file_name);
int		init_map(t_cub *cub, char **argv);
int		init_mlx(t_cub *cub);
int		init_texture(t_cub *cub);
int		is_wall(t_data *data, int x, int y);
int		parsing_map(t_cub *cub, char **argv);
int		put_pixel(t_data *data, int x, int y, int color);;

double	distance_to_wall(t_cub *cub, t_vector coef, int sign, int ray);
double	fix_fisheye(t_cub *cub, int i);
double	get_angle(double angle, int rotation);

void	draw_player_body(t_cub *cub);
void	display_images(t_cub *cub);
void	free_cub(t_cub *cub);
void	generate_minimap(t_cub *cub);
void	generate_player(t_cub *cub);
void	generate_3d(t_cub *cub);
void	init_camera(t_cub *cub);
void	init_raycasting(t_cub *cub);
void	init_side_wall(t_cub *cub, t_data *minimap, int ray);;
void	move_player(t_cub *cub, t_vector coef, int sign);
void	render_minimap(t_cub *cub);

int		parse_xpm(t_cub *cub);
int		is_valid_number(char *rgb);
void	save_texture(int *fd, char *path, char **path_save);

double	new_distance_to_wall(t_cub *cub, t_vector coef, int sign, int ray);

#endif