/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:59:47 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/25 16:28:34 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

static void	display_map(t_map *map)
{
	for (int i = 0; i < map->height; i++)
		printf("%s\n", map->array[i]);
}

void	init_raycasting(t_cub *cub)
{
	// t_mlx	mlx;
	// int		pos_x = 1;
	// int		pos_y = 1;
	// int		d_x = 1;
	// int		d_y = 1;
	// char		aim = 'N';

	display_map(cub->map);
	init_mlx(cub);
	// j'ai besoin de la position de depart du personnage ET orientation
}