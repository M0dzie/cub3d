/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:20:01 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/06/28 13:49:15 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft/includes/libft.h"
# include "mlx_linux/mlx.h"
# include <stdio.h>
# include <math.h>

# ifndef GRID_MINI
#  define GRID_MINI 128
# endif

// # ifndef GRID_MAP
// #  define GRID_MAP 100
// # endif

# define WIN_WIDTH 1980.0
# define WIN_HEIGHT 1080.0
// # define WIN_WIDTH 1280.0
// # define WIN_HEIGHT 720.0

# define SPEED_MINI 8.0
# define SPEED_ANGLE 2.0

# define FOV 90.0

# ifndef COLORS
#  define WALL_COLOR 0x00202020
#  define NORTH 0x00202021
#  define SOUTH 0x00202022
#  define WEST 0x00202023
#  define EAST 0x00202024
# endif

# ifndef KEYS
#  define ESC 65307
#  define W 119
#  define A 97
#  define S 115
#  define D 100
#  define M 109
#  define L_ARROW 65361
#  define R_ARROW 65363
// #  define ESC 53
// #  define W 13
// #  define A 0
// #  define S 1
// #  define D 2
// #  define M 46
// #  define L_ARROW 123
// #  define R_ARROW 124
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
	int		*data;
}			t_data;

typedef struct s_map
{
	int		map_x;
	int		map_y;
	int		width;
	int		height;
	char	**array;

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

typedef struct s_ray_map
{
	int				side;
	double			coef;
	double			dist;
	double			angle;
	// t_vector	coef_we;
	t_vector		pos;
	t_vector		dir;
	t_vector		wall;
	t_vector		coef_ns;
	t_vector		next_inter;
	t_vector		dist_next_inter;
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

typedef struct s_player
{
	t_ray		pos;
	double		coef;
	t_vector	dir;
	t_vector	fov;
	t_vector	pos_3d;
	t_ray_map	**ray;
}				t_player;

typedef struct s_imgs
{
	// int		show_mini;
	t_data	back;
	t_data	game;
	t_data	minimap;
	// t_data	p;
}			t_imgs;

typedef struct s_xpm
{
	int		fd;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*addr;
	int		*data;
	char	*path;
	void	*tex;
	int		*px;
}			t_xpm;

typedef struct s_cub
{
	t_xpm	north;
	t_xpm	south;
	t_xpm	west;
	t_xpm	east;

	int				floor;
	int				roof;
	int 			*rgb_floor;
	int 			*rgb_roof;
	char			*file;
	char			**file_split;
	void			*mlx;
	void			*win;
	t_imgs			*imgs;
	struct s_map	*map;
	struct s_player	*p;
}					t_cub;

int		are_rgb_valid(t_cub *cub);
int		calcul_coef(t_cub *cub);
int		check_border(t_cub *cub);
int		display_error(char *name, int num_error);
int		display_error_texture(t_cub *cub);
int		exit_cub(t_cub *cub);
int		get_pixel(t_xpm tex, int x, int y);
int		init_color(t_cub *cub);
int		init_file(t_cub *cub, char *file_name);
int		init_map(t_cub *cub, char **argv);
int		init_texture(t_cub *cub);
int		is_wall(t_data *data, int x, int y);
int		parsing_map(t_cub *cub, char **argv);
int		parse_xpm(t_cub *cub);
int		put_pixel(t_data *data, int x, int y, int color);

int		init_mlx(t_cub *cub);

double	distance_to_wall(t_cub *cub, t_vector coef, int sign, int ray);
double	fix_fisheye(t_cub *cub, int i);
double	get_angle(double angle, int rotation);
double	get_radian(double angle);

void	draw_player_body(t_cub *cub);
void	display_images(t_cub *cub);
void	generate_minimap(t_cub *cub);
void	generate_player(t_cub *cub);
void	generate_3d(t_cub *cub);
void	init_camera(t_cub *cub);
void	init_raycasting(t_cub *cub);
void	init_side_wall(t_cub *cub, t_data *minimap, int ray);;
void	move_player(t_cub *cub, t_vector coef, int sign);
void	save_texture(int *fd, char *path, char **path_save);

int		render_cub3d(t_cub *cub);

#endif