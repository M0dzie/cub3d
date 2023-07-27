/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:23:45 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/27 17:25:10 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	parse_player_angle(t_cub *cub, char c)
{
	if (c == 'N')
		cub->p->pos.angle = 0;
	else if (c == 'S')
		cub->p->pos.angle = 180;
	else if (c == 'W')
		cub->p->pos.angle = 270;
	else if (c == 'E')
		cub->p->pos.angle = 90;
}

static int	malloc_player(t_cub *cub)
{
	int	i;

	cub->p = malloc(sizeof(t_player));
	if (!cub->p)
		return (display_error("cub->p", 4));
	cub->p->ray = ft_calloc(WIN_WIDTH + 1, sizeof(t_ray_map *));
	if (!cub->p->ray)
		return (display_error("cub->p->ray", 4));
	i = -1;
	while (++i < WIN_WIDTH)
	{
		cub->p->ray[i] = malloc(sizeof(t_ray_map));
		if (!cub->p->ray[i])
			return (display_error("cub->p->ray[i]", 4));
	}
	return (0);
}

int	init_player(t_cub *cub)
{
	int		i;
	int		j;
	char	c;

	if (malloc_player(cub) != 0)
		return (-1);
	cub->p->coef = FOV / WIN_WIDTH;
	i = -1;
	while (cub->map->array[++i])
	{
		j = -1;
		while (cub->map->array[i][++j])
		{
			c = cub->map->array[i][j];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
			{
				parse_player_angle(cub, c);
				cub->p->pos.start.x = j * GRID + GRID / 2;
				cub->p->pos.start.y = i * GRID + (GRID / 2 - GRID / 2);
			}
		}
	}
	return (0);
}
