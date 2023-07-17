/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:20:20 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/07/17 13:27:08 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rotate_player(t_cub *cub, int sign)
{
	double	tmp;

	tmp = cub->p->axis.x;
	cub->p->axis.x = cub->p->axis.x * cub->cos_angle - cub->p->axis.y * \
	(cub->sin_angle * sign);
	cub->p->axis.y = cub->p->axis.y * cub->cos_angle + tmp * \
	(cub->sin_angle * sign);
	tmp = cub->p->axis_side.x;
	cub->p->axis_side.x = cub->p->axis_side.x * cub->cos_angle - \
	cub->p->axis_side.y * (cub->sin_angle * sign);
	cub->p->axis_side.y = cub->p->axis_side.y * cub->cos_angle + tmp * \
	(cub->sin_angle * sign);
	tmp = cub->p->fov.x;
	cub->p->fov.x = cub->p->fov.x * cub->cos_angle - cub->p->fov.y * \
	(cub->sin_angle * sign);
	cub->p->fov.y = cub->p->fov.y * cub->cos_angle + tmp * \
	(cub->sin_angle * sign);
}

static int	is_blocked(double x, double y, char **map)
{
	if (map[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

void	move_player(t_cub *cub, t_vector axis, int sign)
{
	double	x;
	double	y;

	x = cub->p->pos.x + (axis.x * SPEED_PLAYER) * sign;
	y = cub->p->pos.y + (axis.y * SPEED_PLAYER) * sign;
	if (is_blocked(x, y, cub->map->array) || is_blocked(x + 0.1, y - 0.1, \
	cub->map->array) || is_blocked(x + 0.1, y + 0.1, cub->map->array) || \
	is_blocked(x - 0.1, y + 0.1, cub->map->array) || is_blocked(x - 0.1, \
	y - 0.1, cub->map->array))
		return ;
	else
	{
		cub->p->pos.x = x;
		cub->p->pos.y = y;
	}
}
