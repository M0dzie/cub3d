/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thomas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:54:07 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/06 17:00:15 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THOMAS_H
# define THOMAS_H
# include "cub3d.h"
# include "mlx/mlx.h"
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

// DEFINE VARIABLE
# ifndef FOV
#  define FOV 66
# endif

typedef struct	s_ray
{
	t_vector	start;
	t_vector	end;
}				t_ray;

void	dda(t_cub *cub);
void	init_camera(t_cub *cub, t_data *data);
void	put_pixel(t_data *data, int x, int y, int color);

#endif
