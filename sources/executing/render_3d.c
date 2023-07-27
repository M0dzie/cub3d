/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:41:02 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/27 17:49:10 by thmeyer          ###   ########.fr       */
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
	(double)GRID / 2) - start.y, 2.0)));
}

static double	fix_fisheye(t_cub *cub, int i)
{
	double	new_angle;
	double	dist;

	new_angle = get_radian(cub->p->ray[i]->angle - cub->p->pos.angle);
	dist = adjust_distance(cub->p->pos.start, cub->p->ray[i]->wall);
	dist /= GRID;
	dist = dist * cos(new_angle);
	return (dist);
}

void	generate_3d(t_cub *cub)
{
	int	x;

	cub->img_cub.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->img_cub.addr = mlx_get_data_addr(cub->img_cub.img, &cub->img_cub.bits_per_pixel, \
	&cub->img_cub.line_length, &cub->img_cub.endian);
	put_floor_and_ceiling(cub);
	x = -1;
	while (cub->p->ray[++x])
	{
		cub->p->ray[x]->dist = fix_fisheye(cub, x);
		cub->p->ray[x]->wall_height = WIN_HEIGHT / cub->p->ray[x]->dist * 1.3;
		cub->p->ray[x]->margin = (WIN_HEIGHT - cub->p->ray[x]->wall_height) / 2;
		cub->p->ray[x]->map.x = cub->p->ray[x]->wall.x / GRID;
		cub->p->ray[x]->map.y = cub->p->ray[x]->wall.y / GRID;
		if (cub->p->ray[x]->margin > 0 && cub->p->ray[x]->margin < WIN_HEIGHT)
			draw_wall(cub, x, cub->p->ray[x]->margin, cub->p->ray[x]->margin + \
			cub->p->ray[x]->wall_height - 1);
		else
			draw_wall(cub, x, 0, WIN_HEIGHT);
	}
}
