/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thomas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:54:07 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/09 00:04:30 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THOMAS_H
# define THOMAS_H
# include "cub3d.h"
// # include "mlx/mlx.h"
# include <stdlib.h>

// KEY MAC
// #  define ESC 53
// #  define W 13
// #  define A 0
// #  define S 1
// #  define D 2
// #  define M 46
// #  define L_ARROW 123
// #  define R_ARROW 124

// typedef struct s_raycaster
// {
// 	t_vector	ray_dir;
// 	t_vector	delta_dist;
// 	t_vector	side_dist;
// 	t_vector	map;
// 	int			step_x;
// 	int			step_y;
// 	int			hit;
// 	int			side;
// 	double		wall_dist;
// }				t_raycaster;

// typedef struct s_player
// {
// 	t_vector	pos;
// 	t_vector	dir;
// 	t_vector	coef_ns;
// 	t_vector	coef_we;
// 	t_vector	start;
// 	t_vector	end;
// 	int			angle;
// }			t_player;

// DEFINE VAR
# ifndef WALL_H
#  define WALL_H 720
# endif

// # ifndef EYE_H
// #  define EYE_H 360
// # endif

// # ifndef CUB_SIZE
// #  define CUB_SIZE 64
// # endif

void	init_camera(t_cub *cub);
int		put_pixel(t_data *data, int x, int y, int color);
int		distance_to_wall(t_cub *cub, t_vector coef, int sign);

#endif
