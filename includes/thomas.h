/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thomas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:54:07 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/29 14:38:21 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THOMAS_H
# define THOMAS_H
# include "cub3d.h"
# include "math.h"
# include "mlx/mlx.h"

// KEY MAC
// #  define ESC 53
// #  define W 13
// #  define A 0
// #  define S 1
// #  define D 2
// #  define M 46
// #  define L_ARROW 123
// #  define R_ARROW 124

typedef struct s_vector2_f
{
	float	x;
	float	y;
}			t_vector2_f;

typedef struct s_vector2_d
{
	double	x;
	double	y;
}			t_vector2_d;

typedef struct s_ray
{
	t_vector2_f	wall_coor;
	t_vector2_d	wall_tiles;
	double		length;
	int			side; // savoir quelle face du mur afficher
	double		angle;
}				t_ray;

void	where_am_i(t_cub *cub);

#endif
