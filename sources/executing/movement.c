/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:20:20 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/08/01 10:50:41 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_blocked(double x, double y, char **map)
{
	if (map[(int)(y / GRID + 0.5)][(int)(x / GRID)] == '1')
		return (1);
	return (0);
}

double	get_angle(double angle, int rotation)
{
	angle += rotation;
	if (angle > 359)
		angle -= 360;
	else if (angle < 0)
		angle += 360;
	return (angle);
}

int	calcul_coef(t_cub *cub)
{
	int		i;
	double	tmp_angle;

	cub->p->pos.coef_ns.x = sin(cub->p->pos.angle * M_PI / 180);
	cub->p->pos.coef_ns.y = -cos(cub->p->pos.angle * M_PI / 180);
	cub->p->pos.coef_we.x = sin((cub->p->pos.angle - 90) * M_PI / 180);
	cub->p->pos.coef_we.y = -cos((cub->p->pos.angle - 90) * M_PI / 180);
	cub->p->pos.coef_nwse.x = sin((cub->p->pos.angle - 45) * M_PI / 180);
	cub->p->pos.coef_nwse.y = -cos((cub->p->pos.angle - 45) * M_PI / 180);
	cub->p->pos.coef_nesw.x = sin((cub->p->pos.angle - 135) * M_PI / 180);
	cub->p->pos.coef_nesw.y = -cos((cub->p->pos.angle - 135) * M_PI / 180);
	tmp_angle = get_angle(cub->p->pos.angle - FOV / 2, 0);
	i = -1;
	while (++i < WIN_WIDTH)
	{
		cub->p->ray[i]->angle = get_angle(tmp_angle + ((i + 1) * cub->p->coef), \
		0);
		cub->p->ray[i]->coef_ns.x = sin(cub->p->ray[i]->angle * M_PI / 180);
		cub->p->ray[i]->coef_ns.y = -cos(cub->p->ray[i]->angle * M_PI / 180);
		find_wall(cub, cub->p->ray[i]->coef_ns, 1, i);
	}
	return (1);
}

void	move_player(t_cub *cub, t_vector coef, int move)
{
	double	x;
	double	y;
	double	hit_box;

	x = cub->p->pos.start.x + (coef.x * MOVE) * move;
	y = cub->p->pos.start.y + (coef.y * MOVE) * move;
	hit_box = GRID * 0.2;
	if (move)
	{
		if (is_blocked(x + hit_box, y - hit_box, cub->map->array) || \
		is_blocked(x + hit_box, y + hit_box, cub->map->array) || \
		is_blocked(x - hit_box, y + hit_box, cub->map->array) || \
		is_blocked(x - hit_box, y - hit_box, cub->map->array))
			return ;
		else
		{
			cub->p->pos.start.x = x;
			cub->p->pos.start.y = y;
		}
	}
	calcul_coef(cub);
}
