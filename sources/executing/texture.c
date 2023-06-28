/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:19:40 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/28 14:19:30 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

void	init_side_wall(t_cub *cub, t_data *minimap, int ray)
{
	char	*dst;

	dst = minimap->addr + (((int)cub->p->ray[ray]->wall.y - 1) * \
	minimap->line_length + ((int)cub->p->ray[ray]->wall.x + (GRID_MINI / 2)) \
	* (minimap->bits_per_pixel / 8));
	cub->p->ray[ray]->side = *(unsigned int *)dst;
}

int	get_pixel(t_xpm tex, int x, int y)
{
	char	*pixel_color;
	int		color;

	if (x < 0 || x > tex.width || y < 0 || y > tex.height)
		return (0);
	pixel_color = tex.addr + y * tex.line_length + x * (tex.bits_per_pixel / 8);
	color = *(unsigned int *)pixel_color;
	return (color);
}

void	render_texture(t_cub *cub)
{
	int	ray;

	ray = -1;
	while (cub->p->ray[++ray])
	{
		int wall_height = (int)(WIN_HEIGHT / cub->p->ray[ray]->dist);
		

		int drawStart = -wall_height / 2 + WIN_HEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = wall_height / 2 + WIN_HEIGHT / 2;
		if(drawEnd >= WIN_HEIGHT)
			drawEnd = WIN_HEIGHT - 1;

		double wall;
		if (cub->p->ray[ray]->side == 0)
			wall = cub->p->pos_3d.y + cub->p->ray[ray]->dist * cub->p->ray[ray]->dir.y;
		else
			wall = cub->p->pos_3d.x + cub->p->ray[ray]->dist * cub->p->ray[ray]->dir.x;
		wall -= floor(wall);

		// x coordinate on the texture
		int texX = (int)(wall * (double)cub->north.width);
		if (cub->p->ray[ray]->side == 0 && cub->p->ray[ray]->dir.x > 0)
			texX = cub->north.width - texX - 1;
		if (cub->p->ray[ray]->side == 1 && cub->p->ray[ray]->dir.y < 0)
			texX = cub->north.width - texX - 1;

		// How much to increase the texture coordinate perscreen pixel
		double step = 1.0 * cub->north.height / wall_height;

		// Starting texture coordinate
		double texPos = (drawStart - WIN_HEIGHT / 2 + wall_height / 2) * step;

		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (cub->north.height - 1);
			texPos += step;

			// define which texture
			int color = cub->north.px[cub->north.height * texY + texX];

			put_pixel(&cub->imgs->game, (int)WIN_WIDTH - ray, y, color);
		}
		if (drawEnd < 0)
			drawEnd = WIN_HEIGHT; //becomes < 0 when the integer overflows

		//draw the floor from drawEnd to the bottom of the screen
		int i = drawEnd;
		while (++i < WIN_HEIGHT)
		{
			put_pixel(&cub->imgs->game, (int)WIN_WIDTH - ray, i, cub->floor);
			put_pixel(&cub->imgs->game, (int)WIN_WIDTH - ray, (int)WIN_HEIGHT - i, cub->roof);
		}
	}
}