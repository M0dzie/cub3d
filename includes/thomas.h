/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thomas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:54:07 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/31 10:23:51 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THOMAS_H
# define THOMAS_H
# include "cub3d.h"
# include "math.h"
# include <limits.h>
# include <stdlib.h>
// # include "mlx/mlx.h"

// KEY MAC
// #  define ESC 53
// #  define W 13
// #  define A 0
// #  define S 1
// #  define D 2
// #  define M 46
// #  define L_ARROW 123
// #  define R_ARROW 124

typedef struct s_raycaster
{
	t_vector	ray_dir;
	t_vector	delta_dist;
	t_vector	side_dist;
	t_vector	map;
	int			step_x;
	int			step_y;
	int			hit;
}				t_raycaster;


void	dda(t_cub *cub);
void	put_pixel(t_data *data, int x, int y, int color);

#endif
