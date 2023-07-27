/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:20:20 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/07/27 01:36:44 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	distance_to_wall(t_cub *cub, t_vector coef, int sign, int ray)
{
	t_vector	tmp;
	t_vector	offset;
	int			tmp_sign;
	double		total_distance;

	tmp.x = cub->p->pos.start.x / GRID;
	tmp.y = cub->p->pos.start.y / GRID + 0.5;
	tmp_sign = -1;
	total_distance = 0.0;
	while (1)
	{
		double distToNextX;
		double distToNextY;
		double numberTimeX;
		double numberTimeY;

		if (coef.x > 0)
			distToNextX = 1 - (tmp.x - (int)tmp.x);
		else
			distToNextX = (tmp.x - (int)tmp.x);
		if (coef.y > 0)
			distToNextY = 1 - (tmp.y - (int)tmp.y);
		else
			distToNextY = (tmp.y - (int)tmp.y);

		if (distToNextX == 0.0)
			distToNextX = 1.0;
		if (distToNextY == 0.0)
			distToNextY = 1.0;

		if (coef.x == 0.0)
			numberTimeX = GRID + 1;
		else
			numberTimeX = distToNextX / (coef.x * sign / GRID) * tmp_sign;
		if (coef.y == 0.0)
			numberTimeY = GRID + 1;
		else
			numberTimeY = distToNextY / (coef.y * sign / GRID) * tmp_sign;

		if (numberTimeX < 0)
			numberTimeX *= -1;
		if (numberTimeY < 0)
			numberTimeY *= -1;

		if (numberTimeX < numberTimeY)
		{
			// 0 to 90 deg angle
			if (coef.x > 0)
			{
				tmp.x += distToNextX;
				offset.x = 0;
			}
			else
			{
				tmp.x += distToNextX * tmp_sign;
				offset.x = 1;
			}
			cub->p->ray[ray]->side = (coef.x > 0);
			tmp.y += (coef.y * numberTimeX * sign / GRID);
			total_distance += numberTimeX;
			offset.y = 0;
		}
		else
		{
			if (coef.y > 0)
			{
				tmp.y += distToNextY;
				offset.y = 0;
			}
			else
			{
				tmp.y += distToNextY * tmp_sign;
				offset.y = 1;
			}
			cub->p->ray[ray]->side = (coef.y > 0) + 2;
			tmp.x += (coef.x * numberTimeY * sign / GRID);
			total_distance += numberTimeY;
			offset.x = 0;
		}
		if (cub->map->array[(int)(tmp.y - offset.y)][(int)(tmp.x - offset.x)] == '1')
		{
			cub->p->ray[ray]->wall.x = tmp.x * GRID;
			cub->p->ray[ray]->wall.y = tmp.y * GRID;
			break ;
		}
	}
	return (total_distance);
}

static int	is_blocked(double x, double y, char **map)
{
	if (map[(int)(y / GRID + 0.5)][(int)(x / GRID)] == '1')
		return (1);
	return (0);
}

void	move_player(t_cub *cub, t_vector coef, int sign)
{
	double		x;
	double		y;

	x = cub->p->pos.start.x + (coef.x * MOVE) * sign;
	y = cub->p->pos.start.y + (coef.y * MOVE) * sign;
	if (sign)
	{
		if (is_blocked(x + 50, y - 50, cub->map->array) || is_blocked(x + 50, \
		y + 50, cub->map->array) || is_blocked(x - 50, y + 50, cub->map->array) \
		|| is_blocked(x - 50, y - 50, cub->map->array))
			return ;
		else
		{
			cub->p->pos.start.x = x;
			cub->p->pos.start.y = y;
		}
	}
	calcul_coef(cub);
}
