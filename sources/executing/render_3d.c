/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:41:02 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/27 11:59:34 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	put_floor_and_ceiling(t_cub *cub)
{
	int	x;
	int	y;

	x = -1;
	while (cub->p->ray[++x])
	{
		y = -1;
		while (++y < WIN_HEIGHT / 2)
			put_pixel(&cub->img_cub, x, y, cub->roof);
		while (++y < WIN_HEIGHT)
			put_pixel(&cub->img_cub, x, y, cub->floor);
	}
}

int	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return (1);
}

void	generate_3d(t_cub *cub)
{
	int	x;

	cub->img_cub.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->img_cub.addr = mlx_get_data_addr(cub->img_cub.img, &cub->img_cub.bits_per_pixel, \
	&cub->img_cub.line_length, &cub->img_cub.endian);
	put_floor_and_ceiling(cub);
	x = -1;
	while (cub->p->ray[++x])
	{
		cub->p->ray[x]->distance = fix_fisheye(cub, x);
		cub->p->ray[x]->wall_height = WIN_HEIGHT / cub->p->ray[x]->distance * 1.3;
		cub->p->ray[x]->margin = (WIN_HEIGHT - cub->p->ray[x]->wall_height) / 2;
		cub->p->ray[x]->map.x = cub->p->ray[x]->wall.x / GRID;
		cub->p->ray[x]->map.y = cub->p->ray[x]->wall.y / GRID;
		if (cub->p->ray[x]->margin > 0 && cub->p->ray[x]->margin < WIN_HEIGHT)
			draw_wall(cub, x, cub->p->ray[x]->margin, cub->p->ray[x]->margin + \
			cub->p->ray[x]->wall_height - 1, cub->p->ray[x]);
		else
			draw_wall(cub, x, 0, WIN_HEIGHT, cub->p->ray[x]);
	}
}
