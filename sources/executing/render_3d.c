/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:41:02 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/13 14:20:04 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

static void	put_floor_and_ceiling(t_cub *cub)
{
	int	x;
	int	y;

	x = -1;
	while (cub->p->ray[++x])
	{
		y = -1;
		while (++y < WIN_HEIGHT / 2)
			put_pixel(&cub->imgs->back, x, y, cub->roof);
		while (++y < WIN_HEIGHT)
			put_pixel(&cub->imgs->back, x, y, cub->floor);
	}
}

static void	draw_wall(t_data *back, int x, int y, int max)
{
	while (y < max)
	{
		put_pixel(back, x, y, 0x413C37);
		y++;
	}
}

void	generate_3d(t_cub *cub)
{
	int		wall_height;
	int		margin;
	int		x;

	if (cub->imgs->back.img)
		mlx_destroy_image(cub->mlx, cub->imgs->back.img);
	cub->imgs->back.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->imgs->back.addr = mlx_get_data_addr(cub->imgs->back.img, &cub->imgs->back.bits_per_pixel, &cub->imgs->back.line_length, &cub->imgs->back.endian);
	x = -1;
	put_floor_and_ceiling(cub);
	while (cub->p->ray[++x])
	{
		cub->p->ray[x]->dist = fix_fisheye(cub, cub->p->ray[x]->dist, x);
		wall_height = WIN_HEIGHT / cub->p->ray[x]->dist * 40;
		margin = (WIN_HEIGHT - wall_height) / 2;
		if (margin > 0 && margin < WIN_HEIGHT)
			draw_wall(&cub->imgs->back, x, margin, margin + wall_height - 1);
		else
			draw_wall(&cub->imgs->back, x, 0, WIN_HEIGHT);
	}
}