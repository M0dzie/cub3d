/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:19:40 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/20 20:54:55 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// static void	init_floor_and_ceiling(t_ray *ray, int *ground, int *ceiling)
// {
// 	*ceiling = -ray->wall_height / 2 + WIN_HEIGHT / 2;
// 	if (*ceiling < 0)
// 		*ceiling = 0;
// 	*ground = ray->wall_height / 2 + WIN_HEIGHT / 2;
// 	if (*ground >= WIN_HEIGHT)
// 		*ground = WIN_HEIGHT;
// }

// static void	init_wall_texture(t_cub *cub, t_ray *ray, int *ceiling, \
// double *wall)
// {
// 	t_xpm	wall_side;

// 	wall_side = cub->west;
// 	if (ray->side == 0)
// 		wall_side = cub->east;
// 	if (ray->side == 1)
// 		wall_side = cub->west;
// 	if (ray->side == 2)
// 		wall_side = cub->south;
// 	if (ray->side == 3)
// 		wall_side = cub->north;
// 	if (ray->side == 0 || ray->side == 1)
// 		*wall = cub->p->pos.y + ray->dist * ray->axis.y;
// 	else
// 		*wall = cub->p->pos.x + ray->dist * ray->axis.x;
// 	*wall -= floor(*wall);
// 	ray->tex.tex_x = (int)(*wall * (double)wall_side.width);
// 	if ((ray->side == 0 || ray->side == 1) && ray->axis.x > 0)
// 		ray->tex.tex_x = wall_side.width - ray->tex.tex_x;
// 	if ((ray->side == 2 || ray->side == 3) && ray->axis.y < 0)
// 		ray->tex.tex_x = wall_side.width - ray->tex.tex_x;
// 	ray->tex.step = 1.0 * wall_side.height / ray->wall_height;
// 	ray->tex.tex_pos = (*ceiling - WIN_HEIGHT / 2 + ray->wall_height / 2) * \
// 	ray->tex.step;
// }

// static void	render_wall(t_cub *cub, t_ray *ray, int n_ray)
// {
// 	int		ground;
// 	int		ceiling;
// 	double	wall;
// 	t_xpm	wall_side;

// 	init_floor_and_ceiling(ray, &ground, &ceiling);
// 	init_wall_texture(cub, ray, &ceiling, &wall);
// 	if (ray->side == 0)
// 		wall_side = cub->east;
// 	if (ray->side == 1)
// 		wall_side = cub->west;
// 	if (ray->side == 2)
// 		wall_side = cub->south;
// 	if (ray->side == 3)
// 		wall_side = cub->north;
// 	while (++ceiling - 1 < ground)
// 	{
// 		ray->tex.tex_y = (int)ray->tex.tex_pos & (wall_side.height - 1);
// 		ray->tex.tex_pos += ray->tex.step;
// 		ray->tex.color = wall_side.px[wall_side.height * ray->tex.tex_y + \
// 		ray->tex.tex_x];
// 		put_pixel(&cub->game, (int)WIN_WIDTH - n_ray, ceiling, \
// 		ray->tex.color);
// 	}
// }

// static void	render_floor_and_ceiling(t_cub *cub, int ray)
// {
// 	int	ground;

// 	ground = cub->p->ray[ray]->wall_height / 2 + WIN_HEIGHT / 2;
// 	if (ground >= WIN_HEIGHT || ground < 0)
// 		ground = WIN_HEIGHT - 1;
// 	while (++ground < WIN_HEIGHT)
// 	{
// 		put_pixel(&cub->game, (int)WIN_WIDTH - ray, ground, cub->floor);
// 		put_pixel(&cub->game, (int)WIN_WIDTH - ray, (int)WIN_HEIGHT - \
// 		ground, cub->roof);
// 	}
// }

// void	render_texture(t_cub *cub)
// {
// 	int	ray;

// 	ray = -1;
// 	while (cub->p->ray[++ray])
// 	{
// 		render_wall(cub, cub->p->ray[ray], ray);
// 		render_floor_and_ceiling(cub, ray);
// 	}
// }

void	init_side_wall(t_cub *cub, t_data *minimap, int ray)
{
	char	*dst;

	dst = minimap->addr + (((int)cub->p->ray[ray]->wall.y - 1) * minimap->line_length + \
	((int)cub->p->ray[ray]->wall.x + (GRID_MINI / 2)) * (minimap->bits_per_pixel / 8));
	cub->p->ray[ray]->side = *(unsigned int *)dst;
}
