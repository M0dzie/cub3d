/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:19:40 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/28 14:42:28 by thmeyer          ###   ########.fr       */
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

void	render_texture(t_cub *cub)
{
	int	ray;

	ray = -1;
	put_floor_and_ceiling(cub);
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
	}
}