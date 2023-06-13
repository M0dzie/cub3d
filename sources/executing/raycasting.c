/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:17:16 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/13 16:11:39 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

static void	init_data_raycaster(t_cub *cub, t_raycaster *ray, int i)
{
	ray->dist.x = sqrt(1 + powf(cub->p->ray[i]->dir.y, 2.0) / \
	powf(cub->p->ray[i]->dir.x, 2.0));
	ray->dist.x = sqrt(1 + powf(cub->p->ray[i]->dir.x, 2.0) / \
	powf(cub->p->ray[i]->dir.y, 2.0));
	ray->hit = 0;
	ray->side = 0;
	ray->map.x = cub->p->pos.start.x / GRID_MINI;
	ray->map.y = cub->p->pos.start.y / GRID_MINI;
	if (cub->p->ray[i]->dir.x < 0)
	{
		ray->step.x = -1;
		ray->next.x = (cub->p->pos.start.x - ray->map.x) * ray->dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->next.x = (ray->map.x + 1 - cub->p->pos.start.x) * ray->dist.x;
	}
	if (cub->p->ray[i]->dir.y < 0)
	{
		ray->step.y = -1;
		ray->next.y = (cub->p->pos.start.y - ray->map.y) * ray->dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->next.y = (ray->map.y + 1 - cub->p->pos.start.y) * ray->dist.y;
	}
}

void	get_next_wall(t_cub *cub, int i)
{
	t_raycaster	ray;

	init_data_raycaster(cub, &ray, i);
	while (!ray.hit)
	{
		if (ray.next.x < ray.next.y)
		{
			ray.next.x += ray.dist.x;
			ray.map.x += ray.step.x;
			ray.side = 0;
		}
		else
		{
			ray.next.y += ray.dist.y;
			ray.map.y += ray.step.y;
			ray.side = 1;
		}
		if (cub->map->array[(int)ray.map.y][(int)ray.map.x] == \
		'1')
			ray.hit = 1;
	}
	if (ray.side == 0)
		cub->p->ray[i]->dist = ray.next.x - ray.dist.x;
	else
		cub->p->ray[i]->dist = ray.next.y - ray.dist.y;
	printf("dist = %lf\n", cub->p->ray[i]->dist);
}