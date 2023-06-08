/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:29:51 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/08 22:57:05 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

static void	draw_sky(t_cub *cub, int height, int x, int *y)
{
	while (++(*y) < (WIN_HEIGHT - height) / 2)
	put_pixel(&cub->imgs->back, x, (*y), 0x0000FF);
}

static void	draw_wall(t_cub *cub, int height, int x, int *y)
{
	while (++(*y) < (WIN_HEIGHT - height) / 2 + height)
	put_pixel(&cub->imgs->back, x, (*y), 0xFFFFFF);
}

static void	draw_floor(t_cub *cub, int x, int *y)
{
	while (++(*y) < WIN_HEIGHT)
	put_pixel(&cub->imgs->back, x, (*y), 0xFF0000);
}

void	init_camera(t_cub *cub)
{
	int	height;
	int	i;
	int	y;

	i = -1;
	// height = WALL_H / cub->p->pos.dist.n;
	// if (height > WIN_HEIGHT || height < 0)
	// 	height = WIN_HEIGHT;
	// printf("dist = %d and height = %d\n", cub->p->pos.dist.n, height);
	while (cub->p->ray[++i])
	{
		y = -1;
		height = WALL_H / cub->p->ray[i]->dist;
		// printf("dist = %d\n", cub->p->ray[i]->dist);
		// printf("angle = %lf\n", cub->p->ray[i]->angle);
		draw_sky(cub, height, i, &y);
		draw_wall(cub, height, i, &y);
		draw_floor(cub, i, &y);
		mlx_put_image_to_window(cub->mlx, cub->win, cub->imgs->back.img, 0, 0);
	}
}
