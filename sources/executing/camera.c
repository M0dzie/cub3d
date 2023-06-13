/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:29:51 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/13 23:30:57 by thmeyer          ###   ########.fr       */
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
	distance = distance * cos(new_angle);
	return (distance);
}
