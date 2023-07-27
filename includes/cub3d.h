/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:20:01 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/07/27 17:26:32 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft/includes/libft.h"
# include "mlx_linux/mlx.h"
# include <stdio.h>
# include <math.h>

# ifndef GRID
#  define GRID 128
# endif

// # define WIN_WIDTH 1980.0
// # define WIN_HEIGHT 1080.0
# define WIN_WIDTH 1280.0
# define WIN_HEIGHT 720.0

# if __linux__
#  define MOVE 6.0
#  define ROTATE 3.0
# elif __APPLE__
#  define MOVE 3.0
#  define ROTATE 2.0
# endif

# define FOV 60.0

# define TRUE 1
# define FALSE 0

# ifndef COLORS
#  define WEST 0
#  define EAST 1
#  define NORTH 2
#  define SOUTH 3
# endif

# ifndef KEYS
#  if __linux__
#   define ESC 65307
#   define W 119
#   define A 97
#   define S 115
#   define D 100
#   define L_ARROW 65361
#   define R_ARROW 65363
#  elif __APPLE__
#   define ESC 53
#   define W 13
#   define A 0
#   define S 1
#   define D 2
#   define L_ARROW 123
#   define R_ARROW 124
#  endif
# endif

typedef struct s_tex_data
{
	int		tex_x;
	int		tex_y;
	int		color;
	double	tex_pos;
	double	step;
}			t_tex_data;

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
	char	*addr;
	void	*tex;
}			t_xpm;

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
	char	**array;
	int		width;
	int		height;
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
	t_tex_data	tex;
	t_vector	coef_ns;
	t_vector	map;
	t_vector	wall;
	double		angle;
	double		distance;
	double		wall_height;
	double		margin;
	int			index_wall;
	int			side;
}				t_ray_map;

typedef struct s_ray
{
	t_vector	coef_ns;
	t_vector	coef_we;
	t_vector	coef_nwse;
	t_vector	coef_nesw;
	t_vector	start;
	double		angle;
	
}				t_ray;

typedef struct	s_raycast
{
	int			n_ray;
	t_vector	tmp;
	t_vector	repeat;
	t_vector	offset;
	t_vector	dist_next;
}				t_raycast;

typedef struct s_player
{
	t_ray_map	**ray;
	t_ray		pos;
	double		coef;
	int			nb_wall;
}				t_player;

typedef struct s_key
{
	int		w;
	int		s;
	int		a;
	int		d;
	int		r_arrow;
	int		l_arrow;
}			t_key;

typedef struct s_cub
{
	void			*mlx;
	void			*win;
	int				fd_north;
	int				fd_south;
	int				fd_west;
	int				fd_east;
	int				floor;
	int				roof;
	int 			*rgb_floor;
	int 			*rgb_roof;
	char			*file;
	char			**file_split;
	t_data			img_cub;
	t_xpm			north;
	t_xpm			south;
	t_xpm			west;
	t_xpm			east;
	t_key			key;
	t_raycast		ray;
	struct s_map	*map;
	struct s_player	*p;
}					t_cub;

int		are_rgb_valid(t_cub *cub);
int		calcul_coef(t_cub *cub);
int		check_border(t_cub *cub);
int		display_error(char *name, int num_error);
int		display_error_texture(t_cub *cub);
int		exit_cub(t_cub *cub, int xpm);
int		init_color(t_cub *cub);
int		init_file(t_cub *cub, char *file_name);
int		init_map(t_cub *cub, char **argv);
int		init_mlx(t_cub *cub);
int		init_player(t_cub *cub);
int		init_texture(t_cub *cub);
int		is_valid_number(char *rgb);
int		parse_xpm(t_cub *cub);
int		parsing_map(t_cub *cub, char **argv);

double	get_angle(double angle, int rotation);

void	draw_wall(t_cub *cub, int x, int y, int max);
void	find_wall(t_cub *cub, t_vector coef, int sign, int ray);
void	generate_3d(t_cub *cub);
void	move_player(t_cub *cub, t_vector coef, int sign);
void	put_floor_and_ceiling(t_cub *cub);
void	save_texture(int *fd, char *path, char **path_save);

#endif