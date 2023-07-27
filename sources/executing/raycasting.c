/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:41:02 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/27 15:28:06 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_dist_next(t_vector tmp, t_vector coef, t_vector *dist_next)
{
	if (coef.x > 0)
		dist_next->x = 1 - (tmp.x - (int)tmp.x);
	else
		dist_next->x = (tmp.x - (int)tmp.x);
	if (coef.y > 0)
		dist_next->y = 1 - (tmp.y - (int)tmp.y);
	else
		dist_next->y = (tmp.y - (int)tmp.y);
	if (dist_next->x == 0.0)
		dist_next->x = 1.0;
	if (dist_next->y == 0.0)
		dist_next->y = 1.0;
}

static t_vector	init_repeat(t_vector coef, t_vector dist_next, int sign, int tmp_sign)
{
	t_vector repeat;

	if (coef.x == 0.0)
		repeat.x = GRID + 1;
	else
		repeat.x = dist_next.x / (coef.x * sign / GRID) * tmp_sign;
	if (coef.y == 0.0)
		repeat.y = GRID + 1;
	else
		repeat.y = dist_next.y / (coef.y * sign / GRID) * tmp_sign;
	if (repeat.x < 0)
		repeat.x *= -1;
	if (repeat.y < 0)
		repeat.y *= -1;	
	return (repeat);
}

static void	init_side_we(t_cub *cub, t_vector coef, int sign, int tmp_sign)
{
	if (coef.x > 0)
	{
		cub->ray.tmp.x += cub->ray.dist_next.x;
		cub->ray.offset.x = 0;
	}
	else
	{
		cub->ray.tmp.x += cub->ray.dist_next.x * tmp_sign;
		cub->ray.offset.x = 1;
	}
	cub->p->ray[cub->ray.n_ray]->side = (coef.x > 0);
	cub->ray.tmp.y += (coef.y * cub->ray.repeat.x * sign / GRID);
	cub->ray.offset.y = 0;
}

static void	init_side_ns(t_cub *cub, t_vector coef, int sign, int tmp_sign)
{
	if (coef.y > 0)
	{
		cub->ray.tmp.y += cub->ray.dist_next.y;
		cub->ray.offset.y = 0;
	}
	else
	{
		cub->ray.tmp.y += cub->ray.dist_next.y * tmp_sign;
		cub->ray.offset.y = 1;
	}
	cub->p->ray[cub->ray.n_ray]->side = (coef.y > 0) + 2;
	cub->ray.tmp.x += (coef.x * cub->ray.repeat.y * sign / GRID);
	cub->ray.offset.x = 0;
}

void	find_wall(t_cub *cub, t_vector coef, int sign, int ray)
{
	int			tmp_sign;

	cub->ray.tmp.x = cub->p->pos.start.x / GRID;
	cub->ray.tmp.y = cub->p->pos.start.y / GRID + 0.5;
	tmp_sign = -1;
	cub->ray.n_ray = ray;
	while (1)
	{
		init_dist_next(cub->ray.tmp, coef, &cub->ray.dist_next);
		cub->ray.repeat = init_repeat(coef, cub->ray.dist_next, sign, tmp_sign);
		if (cub->ray.repeat.x < cub->ray.repeat.y)
			init_side_we(cub, coef, sign, tmp_sign);
		else
			init_side_ns(cub, coef, sign, tmp_sign);
		if (cub->map->array[(int)(cub->ray.tmp.y - cub->ray.offset.y)]\
		[(int)(cub->ray.tmp.x - cub->ray.offset.x)] == '1')
		{
			cub->p->ray[ray]->wall.x = cub->ray.tmp.x * GRID;
			cub->p->ray[ray]->wall.y = cub->ray.tmp.y * GRID;
			break ;
		}
	}
}
