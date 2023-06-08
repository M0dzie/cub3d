/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:29:51 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/08 21:49:36 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

static void	draw_sky(t_cub *cub, int height, int *y)
{
	int	x;
	int	tmp_y;

	x = 0;
	tmp_y = (*y);
	while (x < WIN_WIDTH)
	{
		(*y) = tmp_y;
		while (++(*y) < (WIN_HEIGHT - height) / 2)
			put_pixel(&cub->imgs->back, x, (*y), 0x0000FF);
		x++;
	}
}

static void	draw_wall(t_cub *cub, int height, int *y)
{
	int	x;
	int	tmp_y;

	x = 0;
	tmp_y = (*y);
	while (x < WIN_WIDTH)
	{
		(*y) = tmp_y;
		while (++(*y) < (WIN_HEIGHT - height) / 2 + height)
			put_pixel(&cub->imgs->back, x, (*y), 0xFFFFFF);
		x++;
	}
}

static void	draw_floor(t_cub *cub, int *y)
{
	int	x;
	int	tmp_y;

	x = 0;
	tmp_y = (*y);
	while (x < WIN_WIDTH)
	{
		(*y) = tmp_y;
		while (++(*y) < WIN_HEIGHT)
			put_pixel(&cub->imgs->back, x, (*y), 0xFF0000);
		x++;
	}
}

void	init_camera(t_cub *cub)
{
	int	height;
	int	y;

	y = -1;
	height = WALL_H / cub->p->pos.dist.n;
	if (height > WIN_HEIGHT || height < 0)
		height = WIN_HEIGHT;
	printf("dist = %d and height = %d\n", cub->p->pos.dist.n, height);
	draw_sky(cub, height, &y);
	draw_wall(cub, height, &y);
	draw_floor(cub, &y);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->imgs->back.img, 0, 0);
}
