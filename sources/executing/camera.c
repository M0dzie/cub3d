/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:29:51 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/08 14:31:16 by thmeyer          ###   ########.fr       */
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
		// while (++(*y) < EYE_H - (height / 2))
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
		// while (++(*y) < EYE_H + (height / 2))
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
	printf("dist = %d and height = %d\n", cub->p->pos.dist.n, height);
	draw_sky(cub, height, &y);
	draw_wall(cub, height, &y);
	draw_floor(cub, &y);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->imgs->back.img, 0, 0);
}

// void	init_camera(t_cub *cub)
// {
// 	int	x;
// 	int	y;
// 	int	height;

// 	// if (cub->imgs->back)
// 	// 	mlx_destroy_image(cub->.imgmlx, cub->imgs->back.img);
// 	// cub->imgs->back.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
// 	// cub->imgs->back.addr = mlx_get_data_addr(cub->imgs->back.img, &cub->imgs->back.bits_per_pixel, &cub->imgs->back.line_length, &cub->imgs->back.endian);
// 	// x = -1 + ((WIN_WIDTH / 2) - 1);
// 	x = -1;
// 	y = -1;
// 	height = WALL_H / cub->p->pos.dist;
// 	printf("dist = %d and height = %d\n", cub->p->pos.dist, height);
// 	// while (++x < (WIN_WIDTH / 2) + 1)
// 	while (++x < WIN_WIDTH)
// 	{
// 		y = -1;
// 		while (++y < EYE_H - (height / 2))
// 			if (cub->p->pos.dist > 0)
// 				put_pixel(&cub->imgs->back, x, y, 0x0000FF);
// 	}
// 	// x = -1 + ((WIN_WIDTH / 2) - 1);
// 	x = -1;
// 	// while (++x < (WIN_WIDTH / 2) + 1)
// 	while (++x < WIN_WIDTH)
// 	{
// 		y = EYE_H - (height / 2);
// 		while (++y < EYE_H + (height / 2))
// 			if (cub->p->pos.dist > 0)
// 				put_pixel(&cub->imgs->back, x, y, 0xFFFFFF);
// 	}
// 	// x = -1 + ((WIN_WIDTH / 2) - 1);
// 	x = -1;
// 	// while (++x < (WIN_WIDTH / 2) + 1)
// 	while (++x < WIN_WIDTH)
// 	{
// 		y = EYE_H + (height / 2);
// 		while (++y < WIN_HEIGHT)
// 			if (cub->p->pos.dist > 0)
// 				put_pixel(&cub->imgs->back, x, y, 0xFF0000);
// 	}
// 	mlx_put_image_to_window(cub->mlx, cub->win, cub->imgs->back.img, 0, 0);
// }
