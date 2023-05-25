/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:43:13 by msapin            #+#    #+#             */
/*   Updated: 2023/05/25 16:30:20 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	render_minimap(t_cub *cub)
{
	mlx_put_image_to_window(cub->mlx, cub->win, cub->imgs->minimap.img, 0, 0);
}

void	move_player(t_cub *cub)
{
	(void)cub;
	render_minimap(cub);
}

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	put_miniwall(t_data data, int start_x, int start_y)
{
	int	y;
	int	x;

	y = -1;
	while (++y < GRID_MINI)
	{
		x = -1;
		while (++x < GRID_MINI)
		{
			if (y == (GRID_MINI - 1) || x == (GRID_MINI - 1) || y == 0 || x == 0)
				put_pixel(&data, x + start_x, y + start_y, 0x00808080);
			else
				put_pixel(&data, x + start_x, y + start_y, 0x00565656);
		}
	}
}

void	generate_minimap(t_cub *cub)
{
	int	y;
	int	x;

	cub->imgs->minimap.img = mlx_new_image(cub->mlx, cub->map->width * GRID_MINI, cub->map->height * GRID_MINI);
	cub->imgs->minimap.addr = mlx_get_data_addr(cub->imgs->minimap.img, &cub->imgs->minimap.bits_per_pixel, &cub->imgs->minimap.line_length, &cub->imgs->minimap.endian);
	y = -1;
	while (++y < (cub->map->height))
	{
		x = -1;
		while (++x < (cub->map->width))
		{
			if (cub->map->array[y][x] == '1')
				put_miniwall(cub->imgs->minimap, x * GRID_MINI, y * GRID_MINI);
		}
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->imgs->minimap.img, 0, 0);
}
