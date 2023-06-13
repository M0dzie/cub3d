/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:29:51 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/13 20:16:42 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

static double	get_radian(double angle)
{
	return (angle * M_PI / 180);
}

// double	adjust_distance(t_cub *cub, int i)
// {
// 	double	distance;

// 	distance = sqrt(powf(cub->p->ray[i]->wall.x - cub->p->pos.start.x, 2.0) + \
// 	powf(cub->p->ray[i]->wall.y - cub->p->pos.start.y, 2.0));
// 	return (distance);
// }

double	fix_fisheye(t_cub *cub, double distance, int i)
{
	double	new_angle;

	new_angle = get_radian(cub->p->ray[i]->angle - cub->p->pos.angle);
	distance = distance * cos(new_angle);
	return (distance);
}
