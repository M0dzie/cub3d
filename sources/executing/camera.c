/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:29:51 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/24 17:21:17 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static double	get_radian(double angle)
{
	return (angle * M_PI / 180);
}

static double	adjust_distance(t_vector start, t_vector wall)
{
	return (sqrt(pow(wall.x - start.x, 2.0) + pow((wall.y - \
	(double)GRID_MINI / 2) - start.y, 2.0)));
}

double	fix_fisheye(t_cub *cub, int i)
{
	double	new_angle;
	double	distance;

	new_angle = get_radian(cub->p->ray[i]->angle - cub->p->pos.angle);
	distance = adjust_distance(cub->p->pos.start, cub->p->ray[i]->wall);
	distance /= GRID_MINI;
	distance = distance * cos(new_angle);
	return (distance);
}
