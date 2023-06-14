/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:29:51 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/14 14:06:59 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

double	get_radian(double angle)
{
	return (angle * M_PI / 180);
}

double	fix_fisheye(t_cub *cub, double distance, int i)
{
	double	new_angle;

	new_angle = get_radian(cub->p->ray[i]->angle - cub->p->pos.angle);
	distance /= GRID_MINI;
	distance = distance * cos(new_angle);
	return (distance);
}
