/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:59:47 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/30 11:15:04 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

static void	display_map(t_map *map)
{
	for (int i = 0; i < map->height; i++)
		printf("%s\n", map->array[i]);
}

// static void	raycaster(t_cub *cub)
// {
// 	cub->mlx = mlx_init();
// 	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");

// 	mlx_hook(cub->win, 2, 1l << 0, check_keycode, cub);
// 	mlx_hook(cub->win, 17, 1l << 0, ft_exit, cub);
// 	mlx_loop(cub->mlx);
// }

void	dda(t_cub *cub)
{
	t_vector	start;
	t_vector	wall;
	t_vector	diff;
	t_vector	inc;
	t_vector	draw;
	double		length;

	// start.x = cub->p->pos_x;
	// start.y = cub->p->pos_y;
	start.x = cub->p->mini_x + GRID_MINI / 4;
	start.y = cub->p->mini_y;
	wall.x = start.x;
	wall.y = 314;
	diff.x = wall.x - start.x;
	diff.y = wall.y - start.y;
	if (diff.x < 0)
		diff.x *= -1;
	if (diff.y < 0)
		diff.y *= -1;
	if (diff.x > diff.y)
		length = diff.x;
	else
		length = diff.y;
	inc.x = diff.x / length;
	inc.y = diff.y / length;
	draw = start;
	while (draw.y != wall.y)
	{
		mlx_pixel_put(cub->mlx, cub->win, draw.x, draw.y, 0xFF0000);
		// draw.x += inc.x;
		draw.y -= inc.y;
	}
	// printf("pos_x = %lf and pos_y = %lf\n", start.x, start.y);
}

void	init_raycasting(t_cub *cub)
{
	(void)display_map;

	// raycaster(cub);
	init_mlx(cub);
}