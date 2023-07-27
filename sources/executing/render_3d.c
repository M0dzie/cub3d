/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:41:02 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/27 01:07:33 by mehdisapin       ###   ########.fr       */
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

static int	get_texture_pixel(t_xpm tex, int x, int y)
{
	char	*dst;

	dst = tex.addr + (y * tex.line_length + x * (tex.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

static void	draw_wall(t_cub *cub, int x, int y, int max, t_ray_map *ray)
{
	t_xpm	tex;
	int tex_x;
	int tex_y;
	int tmp_y;

	if (ray->side == EAST)
	{
		tex = cub->east;
		tex_x = (cub->p->ray[x]->map.y - (int)cub->p->ray[x]->map.y) * tex.width;
	}
	else if (ray->side == WEST)
	{
		tex = cub->west;
		tex_x = (cub->p->ray[x]->map.y - (int)cub->p->ray[x]->map.y) * tex.width;
		tex_x = tex.width - tex_x - 1;
	}
	else if (ray->side == SOUTH)
	{
		tex = cub->south;
		tex_x = (cub->p->ray[x]->map.x - (int)cub->p->ray[x]->map.x) * tex.width;
		tex_x = tex.width - tex_x - 1;
	}
	else
	{
		tex = cub->north;
		tex_x = (cub->p->ray[x]->map.x - (int)cub->p->ray[x]->map.x) * tex.width;
	}
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

void	generate_3d(t_cub *cub)
{
	int	x;

	cub->img_cub.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->img_cub.addr = mlx_get_data_addr(cub->img_cub.img, &cub->img_cub.bits_per_pixel, &cub->img_cub.line_length, &cub->img_cub.endian);
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
			draw_wall(cub, x, cub->p->ray[x]->margin, cub->p->ray[x]->margin + cub->p->ray[x]->wall_height - 1, cub->p->ray[x]);
		else
			draw_wall(cub, x, 0, WIN_HEIGHT, cub->p->ray[x]);
	}
}
