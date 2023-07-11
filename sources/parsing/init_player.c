/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:19:52 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/11 12:24:04 by thmeyer          ###   ########.fr       */
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
		cub->p->dir.x = -1.0;
		cub->p->dir.y = 0.0;
		cub->p->dir_ew.x = 0.0;
		cub->p->dir_ew.y = 1.0;
		cub->p->fov.x = 0.0;
		cub->p->fov.y = 0.66;
	}
	else if (side == 'E')
	{
		cub->p->dir.x = 1.0;
		cub->p->dir.y = 0.0;
		cub->p->dir_ew.x = 0.0;
		cub->p->dir_ew.y = -1.0;
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
		cub->p->dir.x = 0.0;
		cub->p->dir.y = -1.0;
		cub->p->dir_ew.x = -1.0;
		cub->p->dir_ew.y = 0.0;
		cub->p->fov.x = -0.66;
		cub->p->fov.y = 0.0;
	}
	else if (side == 'S')
	{
		cub->p->dir.x = 0.0;
		cub->p->dir.y = 1.0;
		cub->p->dir_ew.x = 1.0;
		cub->p->dir_ew.y = 0.0;
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
				cub->p->pos_3d.x = j + 0.5;
				cub->p->pos_3d.y = i + 0.5;
				init_pos(cub, c);
			}
		}
	}
	return (0);
}