/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:19:40 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/27 13:27:42 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return (1);
}

static int	get_texture_pixel(t_xpm tex, int x, int y)
{
	char	*dst;

	dst = tex.addr + (y * tex.line_length + x * (tex.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

static void	init_texture_and_x(t_cub *cub, t_xpm *tex, int *tex_x, int x)
{
	if (cub->p->ray[x]->side == EAST)
	{
		*tex = cub->east;
		*tex_x = (cub->p->ray[x]->map.y - (int)cub->p->ray[x]->map.y) * tex->width;
	}
	else if (cub->p->ray[x]->side == WEST)
	{
		*tex = cub->west;
		*tex_x = (cub->p->ray[x]->map.y - (int)cub->p->ray[x]->map.y) * tex->width;
		*tex_x = tex->width - *tex_x - 1;
	}
	else if (cub->p->ray[x]->side == SOUTH)
	{
		*tex = cub->south;
		*tex_x = (cub->p->ray[x]->map.x - (int)cub->p->ray[x]->map.x) * tex->width;
		*tex_x = tex->width - *tex_x - 1;
	}
	else
	{
		*tex = cub->north;
		*tex_x = (cub->p->ray[x]->map.x - (int)cub->p->ray[x]->map.x) * tex->width;
	}
}

void	put_floor_and_ceiling(t_cub *cub)
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

void	draw_wall(t_cub *cub, int x, int y, int max)
{
	t_xpm	tex;
	int tex_x;
	int tex_y;
	int tmp_y;

	init_texture_and_x(cub, &tex, &tex_x, x);
	if (cub->p->ray[x]->wall_height > WIN_HEIGHT)
		tmp_y = fabs((max / 2) - (cub->p->ray[x]->wall_height / 2));
	else
		tmp_y = 0;
	while (y < max)
	{
		tex_y = tmp_y * (tex.height / cub->p->ray[x]->wall_height);
		int color = get_texture_pixel(tex, tex_x, tex_y);
		put_pixel(&cub->img_cub, x, y, color);
		tmp_y++;
		y++;
	}
}
