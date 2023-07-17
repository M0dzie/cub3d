/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:20:01 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/07/17 10:18:02 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft/includes/libft.h"
# include "mlx_linux/mlx.h"
# include <stdio.h>
# include <math.h>

# define WIN_WIDTH 1980.0
# define WIN_HEIGHT 1080.0
// # define WIN_WIDTH 1280.0
// # define WIN_HEIGHT 720.0

# define SPEED_PLAYER 0.1
# define SPEED_ANGLE 0.1

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
	int		map_x;
	int		map_y;
	int		width;
	int		height;
	char	**array;
}			t_map;

typedef struct s_tex_data
{
	int		tex_x;
	int		tex_y;
	int		color;
	double	tex_pos;
	double	step;
}			t_tex_data;

typedef struct s_ray
{
	int				side;
	int				wall_height;
	double			coef;
	double			dist;
	t_vector		dir;
	t_vector		next_inter;
	t_vector		dist_next_inter;
	t_tex_data		tex;
}					t_ray;

typedef struct s_player
{
	t_vector	dir;
	t_vector	dir_ew;
	t_vector	fov;
	t_vector	pos;
	t_ray		**ray;
}				t_player;

typedef struct s_imgs
{
	t_data	game;
}			t_imgs;

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

typedef struct s_cub
{
	int				floor;
	int				roof;
	int				*rgb_floor;
	int				*rgb_roof;
	char			*file;
	char			**file_split;
	void			*mlx;
	void			*win;
	double			cos_angle;
	double			sin_angle;
	t_xpm			north;
	t_xpm			south;
	t_xpm			west;
	t_xpm			east;
	t_imgs			*imgs;
	struct s_map	*map;
	struct s_player	*p;
}					t_cub;

int		are_rgb_valid(t_cub *cub);
int		check_border(t_cub *cub);
int		display_error(char *name, int num_error);
int		display_error_texture(t_cub *cub);
int		exit_cub(t_cub *cub);
int		init_color(t_cub *cub);
int		init_file(t_cub *cub, char *file_name);
int		init_map(t_cub *cub, char **argv);
int		init_mlx(t_cub *cub);
int		init_player(t_cub *cub);
int		init_texture(t_cub *cub);
int		is_valid_number(char *rgb);
int		parsing_map(t_cub *cub, char **argv);
int		parse_xpm(t_cub *cub);
int		put_pixel(t_data *data, int x, int y, int color);
int		render_cub3d(t_cub *cub);

void	init_raycasting(t_cub *cub);
void	move_player(t_cub *cub, t_vector coef, int sign);
void	render_texture(t_cub *cub);
void	rotate_player(t_cub *cub, int sign);
void	save_texture(int *fd, char *path, char **path_save);

#endif