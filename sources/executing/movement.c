/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:20:20 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/07/27 13:20:16 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
