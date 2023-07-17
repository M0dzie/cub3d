/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:19:52 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/17 13:14:28 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	malloc_player(t_cub *cub)
{
	int	i;

	cub->p = malloc(sizeof(t_player));
	if (!cub->p)
		return (display_error("cub->p", 4));
	cub->p->ray = ft_calloc(WIN_WIDTH + 1, sizeof(t_ray *));
	if (!cub->p->ray)
		return (display_error("cub->p->ray", 4));
	i = -1;
	while (++i < WIN_WIDTH)
	{
		cub->p->ray[i] = malloc(sizeof(t_ray));
		if (!cub->p->ray[i])
			return (display_error("cub->p->ray[i]", 4));
	}
	return (0);
}

static void	init_west_and_east(t_cub *cub, char side)
{
	if (side == 'W')
	{
		cub->p->axis.x = -1.0;
		cub->p->axis.y = 0.0;
		cub->p->axis_side.x = 0.0;
		cub->p->axis_side.y = 1.0;
		cub->p->fov.x = 0.0;
		cub->p->fov.y = 0.66;
	}
	else if (side == 'E')
	{
		cub->p->axis.x = 1.0;
		cub->p->axis.y = 0.0;
		cub->p->axis_side.x = 0.0;
		cub->p->axis_side.y = -1.0;
		cub->p->fov.x = 0.0;
		cub->p->fov.y = -0.66;
	}
}

static void	init_pos(t_cub *cub, char side)
{
	cub->cos_angle = cos(SPEED_ANGLE);
	cub->sin_angle = sin(SPEED_ANGLE);
	if (side == 'N')
	{
		cub->p->axis.x = 0.0;
		cub->p->axis.y = -1.0;
		cub->p->axis_side.x = -1.0;
		cub->p->axis_side.y = 0.0;
		cub->p->fov.x = -0.66;
		cub->p->fov.y = 0.0;
	}
	else if (side == 'S')
	{
		cub->p->axis.x = 0.0;
		cub->p->axis.y = 1.0;
		cub->p->axis_side.x = 1.0;
		cub->p->axis_side.y = 0.0;
		cub->p->fov.x = 0.66;
		cub->p->fov.y = 0.0;
	}
	else
		init_west_and_east(cub, side);
}

int	init_player(t_cub *cub)
{
	int		i;
	int		j;
	char	c;

	if (malloc_player(cub) != 0)
		return (-1);
	i = -1;
	while (cub->map->array[++i])
	{
		j = -1;
		while (cub->map->array[i][++j])
		{
			c = cub->map->array[i][j];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
			{
				cub->p->pos.x = j + 0.5;
				cub->p->pos.y = i + 0.5;
				init_pos(cub, c);
			}
		}
	}
	return (0);
}
