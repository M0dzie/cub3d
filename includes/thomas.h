/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thomas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:54:07 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/13 16:05:14 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THOMAS_H
# define THOMAS_H
# include "cub3d.h"
// # include "mlx/mlx.h"
# include <stdlib.h>

typedef struct s_raycaster
{
	t_vector	dist;
	t_vector	map;
	t_vector	next;
	t_vector	step;
	int			hit;
	int			side;
}				t_raycaster;

void	get_next_wall(t_cub *cub, int i);

#endif
