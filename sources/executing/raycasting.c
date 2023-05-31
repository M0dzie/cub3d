/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:59:47 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/31 10:55:56 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

void	dda(t_cub *cub)
{
	t_vector	start;
	t_vector	wall;
	t_vector	diff;
	t_vector	inc;
	t_vector	draw;
	double		length;

	// start.x = cub->p->pos_x;
	// start.y = cub->p->pos_y;
	start.x = cub->p->mini_x + GRID_MINI / 4;
	start.y = cub->p->mini_y;
	wall.x = start.x;
	wall.y = 314;
	diff.x = wall.x - start.x;
	diff.y = wall.y - start.y;
	if (diff.x < 0)
		diff.x *= -1;
	if (diff.y < 0)
		diff.y *= -1;
	if (diff.x > diff.y)
		length = diff.x;
	else
		length = diff.y;
	inc.x = diff.x / length;
	inc.y = diff.y / length;
	draw = start;
	while (draw.y != wall.y)
	{
		mlx_pixel_put(cub->mlx, cub->win, draw.x, draw.y, 0xFF0000);
		// draw.x += inc.x;
		draw.y -= inc.y;
	}
	printf("pos_x = %lf and pos_y = %lf\n", start.x, start.y);
}

static void	init_step_and_side_dist(t_cub *cub, t_raycaster *raycaster)
{
	if (raycaster->ray_dir.x < 0)
	{
		raycaster->step_x = -1;
		raycaster->side_dist.x = (cub->p->pos.x - raycaster->map.x) * \
		raycaster->delta_dist.x;
	}
	else
	{
		raycaster->step_x = 1;
		raycaster->side_dist.x = (raycaster->map.x + 1 - cub->p->pos.x) * \
		raycaster->delta_dist.x;
	}
	if (raycaster->ray_dir.y < 0)
	{
		raycaster->step_y = -1;
		raycaster->side_dist.y = (cub->p->pos.y - raycaster->map.y) * \
		raycaster->delta_dist.y;
	}
	else
	{
		raycaster->step_y = 1;
		raycaster->side_dist.y = (raycaster->map.y + 1 - cub->p->pos.y) * \
		raycaster->delta_dist.y;
	}
	printf("side_dist.x = %lf and side_dist.y = %lf\n", raycaster->side_dist.x, raycaster->side_dist.y);
}

static void	init_data_raycaster(t_cub *cub, t_raycaster *raycaster)
{
	printf("pos.x = %lf and pos.y = %lf\n", cub->p->pos.x, cub->p->pos.y);
	printf("dir.x = %lf and dir.y = %lf\n", cub->p->dir.x, cub->p->dir.y);
	// raycaster->ray_dir.x = cub->p->dir.x + angle;
	// raycaster->ray_dir.y = cub->p->dir.y + angle;
	raycaster->ray_dir = cub->p->dir;
	raycaster->delta_dist.x = sqrt(1 + (raycaster->ray_dir.y * \
	raycaster->ray_dir.y) / (raycaster->ray_dir.x * raycaster->ray_dir.x));
	raycaster->delta_dist.y = sqrt(1 + (raycaster->ray_dir.x * \
	raycaster->ray_dir.x) / (raycaster->ray_dir.y * raycaster->ray_dir.y));
	raycaster->hit = 0;
	raycaster->step_x = 0;
	raycaster->step_y = 0;
	raycaster->map = cub->p->pos;
	printf("ray_dir.x = %lf and ray_dir.y = %lf\n", raycaster->ray_dir.x, raycaster->ray_dir.y);
	printf("delta_dist.x = %lf and delta_dist.y = %lf\n", raycaster->delta_dist.x, raycaster->delta_dist.y);
	init_step_and_side_dist(cub, raycaster);
}

static void	get_next_wall(t_cub *cub, t_raycaster *raycaster)
{
	while (!raycaster->hit)
	{
		if (raycaster->side_dist.x < raycaster->side_dist.y)
		{
			raycaster->side_dist.x += raycaster->delta_dist.x;
			raycaster->map.x += raycaster->step_x;
		}
		else
		{
			raycaster->side_dist.y += raycaster->delta_dist.y;
			raycaster->map.y += raycaster->step_y;
		}
		if (cub->map->array[(int)raycaster->map.y][(int)raycaster->map.x] == \
		'1')
			raycaster->hit = 1;
	}
	printf("next_wall => map.x = %lf and map.y = %lf\n", raycaster->map.x, raycaster->map.y);
}

void	init_raycasting(t_cub *cub)
{
	t_raycaster	raycaster;

	init_data_raycaster(cub, &raycaster);
	get_next_wall(cub, &raycaster);
	dda(cub);
	init_mlx(cub);
}