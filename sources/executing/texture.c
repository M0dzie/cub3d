/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:19:40 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/27 11:59:38 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	get_texture_pixel(t_xpm tex, int x, int y)
{
	char	*dst;

	dst = tex.addr + (y * tex.line_length + x * (tex.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	draw_wall(t_cub *cub, int x, int y, int max, t_ray_map *ray)
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

void	init_side_wall(t_cub *cub, t_data *minimap, int ray)
{
	(void)cub;
	(void)minimap;
	(void)ray;
	// char	*dst;

	// dst = minimap->addr + (((int)cub->p->ray[ray]->wall.y - 1) * minimap->line_length + \
	// ((int)cub->p->ray[ray]->wall.x + (GRID / 2)) * (minimap->bits_per_pixel / 8));
	// cub->p->ray[ray]->side = *(unsigned int *)dst;
}
