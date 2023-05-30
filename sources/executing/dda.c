/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:03:31 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/30 15:15:14 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

/**
 * @brief Digital Differential Analyzer
 * dda is an algorithm for drawing approximations of line segments
*/
void	dda(t_cub *cub)
{
	t_vector	pos;
	t_vector	dir;

	(void) pos;
	(void) dir;

// position de depart en tiles
	pos.x = 4;
	pos.y = 3;
	if (cub->p->orien == 'N')
	{
		dir.x = 0;
		dir.y = -1;
	}
	if (cub->p->orien == 'S')
	{
		dir.x = 0;
		dir.y = 1;
	}
	if (cub->p->orien == 'E')
	{
		dir.x = 1;
		dir.y = 0;
	}
	if (cub->p->orien == 'W')
	{
		dir.x = 1;
		dir.y = 0;
	}

	t_vector	ray_dir;
	t_vector	delta_dist;
	// ray_dir.x = dir.x + angle;
	// ray_dir.y = dir.y + angle;
	ray_dir = dir;
	delta_dist.x = sqrt(1 + (ray_dir.y * ray_dir.y) / (ray_dir.x * ray_dir.x));
	delta_dist.y = sqrt(1 + (ray_dir.x * ray_dir.x) / (ray_dir.y * ray_dir.y));

	t_vector	side_dist;
	t_vector	map;
	int			step_x;
	int			step_y;
	int			hit;
	hit  = 0;
	step_x  = 0;
	step_y  = 0;
	map = pos;
	if (ray_dir.x < 0)
	{
		step_x = -1;
		side_dist.x = (pos.x - map.x) * delta_dist.x;
	}
	else
	{
		step_x = 1;
		side_dist.x = (map.x + 1 - pos.x) * delta_dist.x;
	}
	if (ray_dir.y < 0)
	{
		step_y = -1;
		side_dist.y = (pos.y - map.y) * delta_dist.y;
	}
	else
	{
		step_y = 1;
		side_dist.y = (map.y + 1 - pos.y) * delta_dist.y;
	}

	printf("delta_dist.x = %lf and delta_dist.y = %lf\n", delta_dist.x, delta_dist.y);
	printf("side_dist.x = %lf and side_dist.y = %lf\n", side_dist.x, side_dist.y);
	while (!hit)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			map.x += step_x;
		}
		else
		{
			side_dist.y += delta_dist.y;
			map.y += step_y;
		}
		if (cub->map->array[(int)map.y][(int)map.x] == 1)
			hit = 1;
	}
	printf("side_dist.x = %lf and side_dist.y = %lf\n", side_dist.x, side_dist.y);
	printf("map.x = %lf and map.y = %lf\n", map.x, map.y);
}
