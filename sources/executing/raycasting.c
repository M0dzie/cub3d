/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:59:47 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/30 12:03:57 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

// void	dda(t_cub *cub)
// {
// 	t_vector	start;
// 	t_vector	wall;
// 	t_vector	diff;
// 	t_vector	inc;
// 	t_vector	draw;
// 	double		length;

// 	// start.x = cub->p->pos_x;
// 	// start.y = cub->p->pos_y;
// 	start.x = cub->p->mini_x + GRID_MINI / 4;
// 	start.y = cub->p->mini_y;
// 	wall.x = start.x;
// 	wall.y = 314;
// 	diff.x = wall.x - start.x;
// 	diff.y = wall.y - start.y;
// 	if (diff.x < 0)
// 		diff.x *= -1;
// 	if (diff.y < 0)
// 		diff.y *= -1;
// 	if (diff.x > diff.y)
// 		length = diff.x;
// 	else
// 		length = diff.y;
// 	inc.x = diff.x / length;
// 	inc.y = diff.y / length;
// 	draw = start;
// 	while (draw.y != wall.y)
// 	{
// 		mlx_pixel_put(cub->mlx, cub->win, draw.x, draw.y, 0xFF0000);
// 		// draw.x += inc.x;
// 		draw.y -= inc.y;
// 	}
	// printf("pos_x = %lf and pos_y = %lf\n", start.x, start.y);
// }

void	init_raycasting(t_cub *cub)
{
	dda(cub);
	init_mlx(cub);
}