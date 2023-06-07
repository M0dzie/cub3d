/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:43:13 by msapin            #+#    #+#             */
/*   Updated: 2023/06/07 14:06:46 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	render_minimap(t_cub *cub)
{
	if (cub->imgs->show_mini)
	{
		generate_minimap(cub);
		generate_player(cub);
	}
}

void	move_player(t_cub *cub)
{
	(void)cub;
	render_minimap(cub);
}

int	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	if (*(unsigned int *)dst == 0x00202020)
		return (0);
	*(unsigned int *)dst = color;
	return (1);
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
			put_pixel(&data, x + start_x, y + start_y, 0x00202020);
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

	if (cub->imgs->minimap.img)
		mlx_destroy_image(cub->mlx, cub->imgs->minimap.img);
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

void	draw_player_body(t_cub *cub)
{
	int	y = -1;

	while (++y < GRID_MINI / 2)
	{
		int	x = -1;
		while (++x < GRID_MINI / 2)
			put_pixel(&cub->imgs->minimap, x + cub->p->pos.start.x, y + cub->p->pos.start.y, 0x0082180e);
	}
}

void	generate_player(t_cub *cub)
{
	t_vector	tmp;

	// draw_player_body(cub);
	tmp.x = cub->p->pos.start.x;
	tmp.y = cub->p->pos.start.y + (double)GRID_MINI / 2;
	cub->p->pos.dist = 0;
	while (1)
	{
		if (tmp.x > 0 && tmp.y > 0)
		{
			if (!put_pixel(&cub->imgs->minimap, tmp.x + GRID_MINI / 2, tmp.y, 0x00ff1500))
				break ;
		}
		else
			break ;
		tmp.x += cub->p->pos.coef_ns.x;
		tmp.y += cub->p->pos.coef_ns.y;
		cub->p->pos.dist++;
	}
	cub->p->pos.dist -= GRID_MINI / 2;
	// printf("count %d\n", cub->p->pos.dist);
}
