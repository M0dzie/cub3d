/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:03:31 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/06 16:12:56 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

/**
 * @brief Digital Differential Analyzer
 * dda is an algorithm for drawing approximations of line segments
*/
// void	dda(t_cub *cub)
// {
// 	t_vector	start;
// 	t_vector	wall;
// 	t_vector	diff;
// 	t_vector	inc;
// 	t_vector	draw;
// 	double		length;

// 	start.x = cub->p->mini_x + GRID_MINI / 4;
// 	start.y = cub->p->mini_y;
// 	// start.x = cub->p->pos.x * GRID_MINI + GRID_MINI / 4;
// 	// start.y = cub->p->pos.y * GRID_MINI;
// 	wall.x = cub->raycaster.map.x * GRID_MINI + GRID_MINI / 4;
// 	wall.y = cub->raycaster.map.y * GRID_MINI;
// 	printf("map.x = %lf and map.y = %lf\n", cub->raycaster.map.x, cub->raycaster.map.y);
// 	printf("start.x = %lf and start.y = %lf\n", start.x, start.y);
// 	printf("wall.x = %lf and wall.y = %lf\n", wall.x, wall.y);
// 	diff.x = wall.x - start.x;
// 	diff.y = wall.y - start.y;
// 	// if (diff.x < 0)
// 	// 	diff.x *= -1;
// 	// if (diff.y < 0)
// 	// 	diff.y *= -1;
// 	if (diff.x > diff.y)
// 		length = diff.x;
// 	else
// 		length = diff.y;
// 	printf("length = %lf\n", length);
// 	inc.x = diff.x / length;
// 	inc.y = diff.y / length;
// 	draw = start;
// 	printf("inc.x = %lf and inc.y = %lf\n", inc.x, inc.y);
// 	while (draw.y != wall.y)
// 	{
// 		mlx_pixel_put(cub->mlx, cub->win, draw.x, draw.y, 0x0007fc03);
// 		draw.x += inc.x;
// 		draw.y += inc.y;
// 	}
// }
