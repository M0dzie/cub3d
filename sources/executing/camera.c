/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:29:51 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/14 16:14:20 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

double	get_radian(double angle)
{
	return (angle * M_PI / 180);
}

double	adjust_distance(t_vector start, t_vector wall)
{
	return (sqrt(pow(wall.x - start.x, 2.0) + pow(wall.y - start.y, 2.0)));
}

double	fix_fisheye(t_cub *cub, int i)
{
	double	new_angle;
	double	distance;

	new_angle = get_radian(cub->p->ray[i]->angle - cub->p->pos.angle);
	// distance = adjust_distance(cub->p->pos.start, cub->p->ray[i]->wall);
	distance = cub->p->ray[i]->dist;
	distance /= GRID_MINI;
	distance = distance * cos(new_angle);
	return (distance);
}
