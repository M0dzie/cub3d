/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:43:13 by msapin            #+#    #+#             */
/*   Updated: 2023/05/25 23:22:35 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	render_minimap(t_cub *cub)
{
	mlx_put_image_to_window(cub->mlx, cub->win, cub->imgs->back.img, 0, 0);
	if (cub->imgs->show_mini)
		mlx_put_image_to_window(cub->mlx, cub->win, cub->imgs->minimap.img, (WIN_WIDTH / 2) - (cub->map->width * GRID_MINI / 2), (WIN_HEIGHT / 2) - (cub->map->height * GRID_MINI / 2));
	mlx_put_image_to_window(cub->mlx, cub->win, cub->imgs->p.img, cub->p->mini_x, cub->p->mini_y);
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
				put_pixel(&data, x + start_x, y + start_y, 0x00202020);
			else
				put_pixel(&data, x + start_x, y + start_y, 0x00202020);
		}
	}
}

void	put_minifloor(t_data data, int start_x, int start_y)
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
				put_pixel(&data, x + start_x, y + start_y, 0x00C6C6C6);
			else
				put_pixel(&data, x + start_x, y + start_y, 0x00CDCDCD);
		}
	}
}

void	generate_minimap(t_cub *cub)
{
	int		y;
	int		x;
	char	c;

	cub->imgs->minimap.img = mlx_new_image(cub->mlx, cub->map->width * GRID_MINI, cub->map->height * GRID_MINI);
	cub->imgs->minimap.addr = mlx_get_data_addr(cub->imgs->minimap.img, &cub->imgs->minimap.bits_per_pixel, &cub->imgs->minimap.line_length, &cub->imgs->minimap.endian);
	y = -1;
	while (++y < (cub->map->height))
	{
		x = -1;
		while (++x < (cub->map->width))
		{
			c = cub->map->array[y][x];
			if (c == '1')
				put_miniwall(cub->imgs->minimap, x * GRID_MINI, y * GRID_MINI);
			else if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
				put_minifloor(cub->imgs->minimap, x * GRID_MINI, y * GRID_MINI);
		}
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->imgs->minimap.img, (WIN_WIDTH / 2) - (cub->map->width * GRID_MINI / 2), (WIN_HEIGHT / 2) - (cub->map->height * GRID_MINI / 2));
}

void	generate_background(t_cub *cub)
{
	int		y;
	int		x;

	cub->imgs->back.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->imgs->back.addr = mlx_get_data_addr(cub->imgs->back.img, &cub->imgs->back.bits_per_pixel, &cub->imgs->back.line_length, &cub->imgs->back.endian);
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			put_pixel(&cub->imgs->back, x, y, 0x006ABED7);
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->imgs->back.img, 0, 0);
}

void	generate_player(t_cub *cub)
{
	int		y;
	int		x;

	cub->imgs->p.img = mlx_new_image(cub->mlx, GRID_MINI / 2, GRID_MINI / 2);
	cub->imgs->p.addr = mlx_get_data_addr(cub->imgs->p.img, &cub->imgs->p.bits_per_pixel, &cub->imgs->p.line_length, &cub->imgs->p.endian);
	y = -1;
	while (++y < GRID_MINI / 2)
	{
		x = -1;
		while (++x < GRID_MINI / 2)
			put_pixel(&cub->imgs->p, x, y, 0x00DE8D4E);
	}
	cub->p->mini_x += ((WIN_WIDTH / 2) - (cub->map->width * GRID_MINI / 2) + GRID_MINI / 4);
	cub->p->mini_y += ((WIN_HEIGHT / 2) - (cub->map->height * GRID_MINI / 2) + GRID_MINI / 4);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->imgs->p.img, cub->p->mini_x, cub->p->mini_y);
}
