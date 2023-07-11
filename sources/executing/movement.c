/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:20:20 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/07/11 11:50:17 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rotate_player(t_cub *cub, int sign)
{
	double	tmp;

	tmp = cub->p->dir.x;
	cub->p->dir.x = cub->p->dir.x * cub->cos_angle - cub->p->dir.y * \
	(cub->sin_angle * sign);
	cub->p->dir.y = cub->p->dir.y * cub->cos_angle + tmp * \
	(cub->sin_angle * sign);
	tmp = cub->p->dir_ew.x;
	cub->p->dir_ew.x = cub->p->dir_ew.x * cub->cos_angle - cub->p->dir_ew.y * \
	(cub->sin_angle * sign);
	cub->p->dir_ew.y = cub->p->dir_ew.y * cub->cos_angle + tmp * \
	(cub->sin_angle * sign);
	tmp = cub->p->fov.x;
	cub->p->fov.x = cub->p->fov.x * cub->cos_angle - cub->p->fov.y * \
	(cub->sin_angle * sign);
	cub->p->fov.y = cub->p->fov.y * cub->cos_angle + tmp * \
	(cub->sin_angle * sign);
}

// add margin to not getting to close of a wall
void	move_player(t_cub *cub, t_vector axis, int sign)
{
	t_vector	tmp_move;

	tmp_move.x = (axis.x * SPEED_PLAYER) * sign;
	tmp_move.y = (axis.y * SPEED_PLAYER) * sign;
	cub->p->pos_3d.x += tmp_move.x;
	cub->p->pos_3d.y += tmp_move.y;
	if (cub->map->array[(int)(cub->p->pos_3d.y)]\
	[(int)(cub->p->pos_3d.x)] == '1')
	{
		cub->p->pos_3d.x -= tmp_move.x;
		cub->p->pos_3d.y -= tmp_move.y;
	}
}
