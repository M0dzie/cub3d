/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:20:01 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/06/17 22:48:34 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft/includes/libft.h"
# include "mlx_linux/mlx.h"
# include <stdio.h>
# include <math.h>

# ifndef GRID_MINI
#  define GRID_MINI 30
# endif

# ifndef GRID_MAP
#  define GRID_MAP 100
# endif

// # define WIN_WIDTH 1980.0
// # define WIN_HEIGHT 1080.0
# define WIN_WIDTH 1280.0
# define WIN_HEIGHT 720.0

# define SPEED_MINI 2.0
# define SPEED_ANGLE 2.0

# define FOV 66.0

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

typedef struct s_ray_map
{
	t_vector		coef_ns;
	t_vector		wall;
	// t_vector	coef_we;
	// t_vector	start;
	// double		dist;
	double			angle;
	unsigned int	side;
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
	t_ray_map	**ray;
	t_ray		pos;
	double		coef;
}				t_player;

typedef struct s_imgs
{
	int		show_mini;
	t_data	minimap;
	t_data	back;
	t_data	p;
}			t_imgs;

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
	struct s_map	*map;
	struct s_player	*p;
}					t_cub;

int		are_rgb_valid(t_cub *cub);
int		calcul_coef(t_cub *cub);
int		check_border(t_cub *cub);
int		display_error(char *name, int num_error);
int		display_error_texture(t_cub *cub);
int		init_color(t_cub *cub);
int		init_file(t_cub *cub, char *file_name);
int		init_map(t_cub *cub, char **argv);
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
void	init_mlx(t_cub *cub);
void	init_raycasting(t_cub *cub);
void	init_side_wall(t_cub *cub, t_data *minimap, int ray);;
void	move_player(t_cub *cub, t_vector coef, int sign);
void	render_minimap(t_cub *cub);

#endif