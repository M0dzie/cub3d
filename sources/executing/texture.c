/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:19:40 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/28 22:53:17 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

static void	render_floor_and_ceiling(t_cub *cub, int wall_height, int ray)
{
	int	ground;

	ground = wall_height / 2 + WIN_HEIGHT / 2;
	if (ground >= WIN_HEIGHT)
		ground = WIN_HEIGHT - 1;
	if (ground < 0)
		ground = WIN_HEIGHT;
	while (++ground < WIN_HEIGHT)
	{
		put_pixel(&cub->imgs->game, (int)WIN_WIDTH - ray, ground, cub->floor);
		put_pixel(&cub->imgs->game, (int)WIN_WIDTH - ray, (int)WIN_HEIGHT - ground, cub->roof);
	}
}

void	render_texture(t_cub *cub)
{
	int	ray;
	int	ground;
	int	ceiling;
	int	wall_height;

	ray = -1;
	// put_floor_and_ceiling(cub);
	while (cub->p->ray[++ray])
	{
		wall_height = (int)(WIN_HEIGHT / cub->p->ray[ray]->dist);
		ceiling = -wall_height / 2 + WIN_HEIGHT / 2;
		if (ceiling < 0)
			ceiling = 0;
		ground = wall_height / 2 + WIN_HEIGHT / 2;
		if (ground >= WIN_HEIGHT)
			ground = WIN_HEIGHT - 1;

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
		double texPos = (ceiling - WIN_HEIGHT / 2 + wall_height / 2) * step;

		for (int y = ceiling; y < ground; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (cub->north.height - 1);
			texPos += step;

			// define which texture
			int color = cub->north.px[cub->north.height * texY + texX];

			put_pixel(&cub->imgs->game, (int)WIN_WIDTH - ray, y, color);
		}
		render_floor_and_ceiling(cub, wall_height, ray);
	}
}