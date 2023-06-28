/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:19:40 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/29 01:23:45 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

static void	init_floor_and_ceiling(t_ray_map *ray, int *ground, int *ceiling)
{
	*ceiling = -ray->wall_height / 2 + WIN_HEIGHT / 2;
	if (*ceiling < 0)
		*ceiling = 0;
	*ground = ray->wall_height / 2 + WIN_HEIGHT / 2;
	if (*ground >= WIN_HEIGHT)
		*ground = WIN_HEIGHT;
}

static void	init_wall_texture(t_cub *cub, t_ray_map *ray, int *ceiling, double *wall)
{
	if (ray->side == 0)
		*wall = cub->p->pos_3d.y + ray->dist * ray->dir.y;
	else
		*wall = cub->p->pos_3d.x + ray->dist * ray->dir.x;
	*wall -= floor(*wall);
	ray->tex.tex_x = (int)(*wall * (double)cub->north.width);
	if (ray->side == 0 && ray->dir.x > 0)
		ray->tex.tex_x = cub->north.width - ray->tex.tex_x - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		ray->tex.tex_x = cub->north.width - ray->tex.tex_x - 1;
	ray->tex.step = 1.0 * cub->north.height / ray->wall_height;
	ray->tex.tex_pos = (*ceiling - WIN_HEIGHT / 2 + ray->wall_height / 2) * ray->tex.step;
}

static void	render_wall(t_cub *cub, t_ray_map *ray, int n_ray)
{
	int		ground;
	int		ceiling;
	double	wall;

	init_floor_and_ceiling(ray, &ground, &ceiling);
	init_wall_texture(cub, ray, &ceiling, &wall);
	while (ceiling < ground)
	{
		ray->tex.tex_y = (int)ray->tex.tex_pos & (cub->north.height - 1);
		ray->tex.tex_pos += ray->tex.step;
		ray->tex.color = cub->north.px[cub->north.height * ray->tex.tex_y + ray->tex.tex_x];
		put_pixel(&cub->imgs->game, (int)WIN_WIDTH - n_ray, ceiling, ray->tex.color);
		ceiling++;
	}
}

static void	render_floor_and_ceiling(t_cub *cub, int ray)
{
	int	ground;

	ground = cub->p->ray[ray]->wall_height / 2 + WIN_HEIGHT / 2;
	if (ground >= WIN_HEIGHT || ground < 0)
		ground = WIN_HEIGHT - 1;
	while (++ground < WIN_HEIGHT)
	{
		put_pixel(&cub->imgs->game, (int)WIN_WIDTH - ray, ground, cub->floor);
		put_pixel(&cub->imgs->game, (int)WIN_WIDTH - ray, (int)WIN_HEIGHT - ground, cub->roof);
	}
}

void	render_texture(t_cub *cub)
{
	int	ray;

	ray = -1;
	while (cub->p->ray[++ray])
	{
		render_wall(cub, cub->p->ray[ray], ray);
		render_floor_and_ceiling(cub, ray);
	}
}