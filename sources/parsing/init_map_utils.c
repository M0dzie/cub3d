/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:41:24 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/05/23 18:02:31 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_surrounded(t_cub *cub, int y, int x)
{
	int	tmp_y;
	int	tmp_x;

	if (y == 0 || y == cub->map->height - 1 || x == 0 \
	|| x == cub->map->width - 1)
		return (0);
	tmp_y = -2;
	while (++tmp_y < 2)
	{
		tmp_x = -2;
		while (++tmp_x < 2)
			if (!cub->map->array[tmp_y + y][tmp_x + x] \
			|| cub->map->array[tmp_y + y][tmp_x + x] == ' ')
				return (0);
	}
	return (1);
}

int	check_border(t_cub *cub)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	while (cub->map->array[++i])
	{
		j = -1;
		while (cub->map->array[i][++j])
		{
			c = cub->map->array[i][j];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
				if (!is_surrounded(cub, i, j))
					return (-1);
		}
	}
	return (0);
}
