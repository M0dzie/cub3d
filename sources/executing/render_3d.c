/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:41:02 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/28 13:25:45 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

static void	define_pos_and_dir(t_cub *cub)
{
	int	ray;

	ray = -1;
	while (cub->p->ray[++ray])
	{
		cub->p->pos_3d.x = cub->p->pos.start.x / GRID_MINI + 0.5;
		cub->p->pos_3d.y = cub->p->pos.start.y / GRID_MINI + 0.5;
		cub->p->ray[ray]->coef = ray * 2 / WIN_WIDTH - 1;
		cub->p->ray[ray]->dir.x = cub->p->dir.x + cub->p->fov.y * \
		cub->p->ray[ray]->coef;
		cub->p->ray[ray]->dir.y = cub->p->dir.y + cub->p->fov.x * \
		cub->p->ray[ray]->coef;
	}
}

// static double	find_next_inter(t_ray_map *ray, t_vector tmp, double mid_angle, \
// int vert)
// {
// 	double		distance;
// 	t_vector	inter;

// 	distance = .0;
// 	if (vert == 1)
// 	{
// 		if (ray->angle > mid_angle)
// 			inter.x = tmp.x + 1;
// 		else if (ray->angle < mid_angle)
// 			inter.x = tmp.x - 0.000000001;
// 		else
// 			inter.x = 0;
// 	}
// 	return (distance);
// }

static int	define_move(t_player *p, t_ray_map *ray, t_map *map, int x)
{
	int	move;

	move = 0;
	if (x == 1)
	{
		if (ray->dir.x < 0)
			return (ray->dist_next_inter.x = (p->pos_3d.x - map->map_x) * \
			ray->next_inter.x, move = -1);
		else
			return (ray->dist_next_inter.x = (map->map_x + 1.0 - p->pos_3d.x) * \
			ray->next_inter.x, move = 1);
	}
	if (ray->dir.y < 0)
		return (ray->dist_next_inter.y = (p->pos_3d.y - map->map_y) * \
		ray->next_inter.y, move = -1);
	else
		return (ray->dist_next_inter.y = (map->map_y + 1.0 - p->pos_3d.y) * \
		ray->next_inter.y, move = 1);
	return (move);
}

void	generate_3d(t_cub *cub)
{
	int		ray;
	int		step_x;
	int		step_y;
	double	distance;

	ray = -1;
	define_pos_and_dir(cub);
	while (cub->p->ray[++ray])
	{
		cub->map->map_x = floor(cub->p->pos_3d.x);
		cub->map->map_y = floor(cub->p->pos_3d.y);
		cub->p->ray[ray]->next_inter.x = fabs(1 / cub->p->ray[ray]->dir.x);
		cub->p->ray[ray]->next_inter.y = fabs(1 / cub->p->ray[ray]->dir.y);
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		step_x = define_move(cub->p, cub->p->ray[ray], cub->map, 1);
		if (cub->p->ray[ray]->dir.y < 0)
		{
			step_y = -1;
			cub->p->ray[ray]->dist_next_inter.y = (cub->p->pos_3d.y - cub->map->map_y) * cub->p->ray[ray]->next_inter.y;
		}
		else
		{
			step_y = 1;
			cub->p->ray[ray]->dist_next_inter.y = (cub->map->map_y + 1.0 - cub->p->pos_3d.y) * cub->p->ray[ray]->next_inter.y;
		}

		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (cub->p->ray[ray]->dist_next_inter.x < cub->p->ray[ray]->dist_next_inter.y)
			{
				cub->p->ray[ray]->dist_next_inter.x += cub->p->ray[ray]->next_inter.x;
				cub->map->map_x += step_x;
				side = 0;
			}
			else
			{
				cub->p->ray[ray]->dist_next_inter.y += cub->p->ray[ray]->next_inter.y;
				cub->map->map_y += step_y;
				side = 1;
			}
			if (cub->map->array[cub->map->map_y][cub->map->map_x] == '1') 
				hit = 1;
		}
		if (side == 0)
			distance = (cub->map->map_x - cub->p->pos_3d.x + (1 - step_x) / 2) / cub->p->ray[ray]->dir.x;
		else
			distance = (cub->map->map_y - cub->p->pos_3d.y + (1 - step_y) / 2) / cub->p->ray[ray]->dir.y;

		int wall_height = (int)(WIN_HEIGHT / distance);
		
		(void)side;

		int drawStart = -wall_height / 2 + WIN_HEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = wall_height / 2 + WIN_HEIGHT / 2;
		if(drawEnd >= WIN_HEIGHT)
			drawEnd = WIN_HEIGHT - 1;

		double wall;
		if (side == 0)
			wall = cub->p->pos_3d.y + distance * cub->p->ray[ray]->dir.y;
		else
			wall = cub->p->pos_3d.x + distance * cub->p->ray[ray]->dir.x;
		wall -= floor(wall);

		// x coordinate on the texture
		int texX = (int)(wall * (double)cub->north.width);
		if (side == 0 && cub->p->ray[ray]->dir.x > 0)
			texX = cub->north.width - texX - 1;
		if (side == 1 && cub->p->ray[ray]->dir.y < 0)
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
