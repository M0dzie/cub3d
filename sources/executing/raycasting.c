/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:59:47 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/06 16:14:54 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

// static void	init_step_and_side_dist(t_cub *cub)
// {
// 	if (cub->raycaster.ray_dir.x < 0)
// 	{
// 		cub->raycaster.step_x = -1;
// 		cub->raycaster.side_dist.x = (cub->p->pos.x - cub->raycaster.map.x) * \
// 		cub->raycaster.delta_dist.x;
// 	}
// 	else
// 	{
// 		cub->raycaster.step_x = 1;
// 		cub->raycaster.side_dist.x = (cub->raycaster.map.x + 1 - cub->p->pos.x) * \
// 		cub->raycaster.delta_dist.x;
// 	}
// 	if (cub->raycaster.ray_dir.y < 0)
// 	{
// 		cub->raycaster.step_y = -1;
// 		cub->raycaster.side_dist.y = (cub->p->pos.y - cub->raycaster.map.y) * \
// 		cub->raycaster.delta_dist.y;
// 	}
// 	else
// 	{
// 		cub->raycaster.step_y = 1;
// 		cub->raycaster.side_dist.y = (cub->raycaster.map.y + 1 - cub->p->pos.y) * \
// 		cub->raycaster.delta_dist.y;
// 	}
// }

// void    init_data_raycaster(t_cub *cub)
// {
//     // printf("pos.x = %lf and pos.y = %lf\n", cub->p->pos.x, cub->p->pos.y);
//     // printf("dir.x = %lf and dir.y = %lf\n", cub->p->dir.x, cub->p->dir.y);
//     cub->raycaster.ray_dir.x = cub->p->dir.x + cub->p->angle;
//     cub->raycaster.ray_dir.y = cub->p->dir.y + cub->p->angle;
//     cub->raycaster.delta_dist.x = sqrt(1 + (cub->raycaster.ray_dir.y * \
//     cub->raycaster.ray_dir.y) / (cub->raycaster.ray_dir.x * cub->raycaster.ray_dir.x));
//     cub->raycaster.delta_dist.y = sqrt(1 + (cub->raycaster.ray_dir.x * \
//     cub->raycaster.ray_dir.x) / (cub->raycaster.ray_dir.y * cub->raycaster.ray_dir.y));
//     cub->raycaster.hit = 0;
//     cub->raycaster.side = 0;
//     cub->raycaster.step_x = 0;
//     cub->raycaster.step_y = 0;
//     cub->raycaster.wall_dist = 0;
//     cub->raycaster.map = cub->p->pos;
//     // printf("ray_dir.x = %lf and ray_dir.y = %lf\n", cub->raycaster.ray_dir.x, cub->raycaster.ray_dir.y);
//     // printf("delta_dist.x = %lf and delta_dist.y = %lf\n", cub->raycaster.delta_dist.x, cub->raycaster.delta_dist.y);
//     init_step_and_side_dist(cub);
// }

// void	get_next_wall(t_cub *cub)
// {
// 	init_data_raycaster(cub);
// 	while (!cub->raycaster.hit)
// 	{
// 		if (cub->raycaster.side_dist.x < cub->raycaster.side_dist.y)
// 		{
// 			cub->raycaster.side_dist.x += cub->raycaster.delta_dist.x;
// 			cub->raycaster.map.x += cub->raycaster.step_x;
// 			cub->raycaster.side = 0;
// 		}
// 		else
// 		{
// 			cub->raycaster.side_dist.y += cub->raycaster.delta_dist.y;
// 			cub->raycaster.map.y += cub->raycaster.step_y;
// 			cub->raycaster.side = 1;
// 		}
// 		if (cub->map->array[(int)cub->raycaster.map.y][(int)cub->raycaster.map.x] == \
// 		'1')
// 			cub->raycaster.hit = 1;
// 	}
// 	// printf("side_dist.x = %lf and side_dist.y = %lf\n", cub->raycaster.side_dist.x, cub->raycaster.side_dist.y);
// 	// printf("next_wall => map.x = %lf and map.y = %lf\n", cub->raycaster.map.x, cub->raycaster.map.y);
// 	if (cub->raycaster.side == 0)
// 		cub->raycaster.wall_dist = cub->raycaster.side_dist.x - cub->raycaster.delta_dist.x;
// 	else
// 		cub->raycaster.wall_dist = cub->raycaster.side_dist.y - cub->raycaster.delta_dist.y;
// 	// printf("wall_dist = %lf\n", cub->raycaster.wall_dist);
// }

// void	init_raycasting(t_cub *cub)
// {
// 	init_mlx(cub);
// }
