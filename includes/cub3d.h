/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:20:01 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/06/06 16:53:46 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft/includes/libft.h"
# include "mlx_linux/mlx.h"
# include <stdio.h>
# include <math.h>

# ifndef GRID_MINI
#  define GRID_MINI 40
# endif

# ifndef GRID_MAP
#  define GRID_MAP 100
# endif

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define SPEED_MINI 5
# define SPEED_ANGLE 5

# ifndef KEYS
#  define ESC 65307
#  define W 119
#  define A 97
#  define S 115
#  define D 100
#  define M 109
#  define L_ARROW 65361
#  define R_ARROW 65363
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

typedef struct    s_ray
{
    t_vector    start;
    t_vector    end;
}                t_ray;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	coef_ns;
	t_vector	coef_we;
	t_vector	start;
	t_vector	end;
	int			angle;
}			t_player;

typedef struct s_imgs
{
	int		show_mini;
	t_data	minimap;
	t_data	back;
	t_data	p;
}			t_imgs;

typedef struct s_raycaster
{
	t_vector	ray_dir;
	t_vector	delta_dist;
	t_vector	side_dist;
	t_vector	map;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		wall_dist;
}				t_raycaster;

typedef struct s_cub
{
	// fds textures, found if better to use fd int or string as path
	int	fd_north;
	int	fd_south;
	int	fd_west;
	int	fd_east;

	int 			*rgb_floor;
	int 			*rgb_roof;
	char			*file;
	char			**file_split;
	struct s_map	*map;
	struct s_player	*p;
	void			*mlx;
	void			*win;
	t_imgs			*imgs;
	t_raycaster		raycaster;
}					t_cub;

int	are_rgb_valid(t_cub *cub);
int	check_border(t_cub *cub);
int	display_error(char *name, int num_error);
int	display_error_texture(t_cub *cub);
int	init_file(t_cub *cub, char *file_name);
int	init_map(t_cub *cub, char **argv);
int	init_texture(t_cub *cub);
int	parsing_map(t_cub *cub, char **argv);

void	generate_background(t_cub *cub);
void	generate_minimap(t_cub *cub);
void	generate_player(t_cub *cub);
void	get_next_wall(t_cub *cub);
void	free_cub(t_cub *cub);
void    init_data_raycaster(t_cub *cub);
void	init_mlx(t_cub *cub);
void	init_raycasting(t_cub *cub);
void	move_player(t_cub *cub);
void	render_minimap(t_cub *cub);

#endif