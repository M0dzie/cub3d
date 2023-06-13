/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:17:16 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/13 23:59:51 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

// double	adjust_distance(double start_x, double start_y, t_vector wall)
// {
// 	return (sqrt(pow(wall.x - start_x, 2.0) + pow(wall.y - start_y, 2.0)));
// }

// double	find_wall_distance(t_cub *cub, t_vector p_pos, double angle, int column)
// {
// 	t_vector	ray;
//     double		a_ray;
//     double		distance;
// 	double		step;
    
//     ray.x = p_pos.x / GRID_MINI;
//     ray.y = p_pos.y / GRID_MINI;
//     distance = 0;
//     step = 0.1;
//     a_ray = angle - FOV / 2 + (double)column / WIN_WIDTH * FOV;
// 	// printf("angle ray = %lf\n", a_ray);
//     while (1)
// 	{
//         ray.x += step * cos(get_radian(a_ray));
//         ray.y += step * sin(get_radian(a_ray));
//        // if (ray.x < 0 || ray.x >= MAP_WIDTH || ray.y < 0 || ray.y >= MAP_HEIGHT) {
//         if (ray.x < 0 || ray.y < 0)
// 		{
//             distance = DIST_MAX;
//             break;
//         }     
//         if (cub->map->array[(int)ray.y][(int)ray.x] == '1')
// 		{
//             distance = adjust_distance(p_pos.x / GRID_MINI, p_pos.y / GRID_MINI, ray) * 30;
//             break;
//         }
//     }
// 	// printf("player.x = %d and player.y = %d\n", (int)cub->p->pos.start.x / GRID_MINI, (int)cub->p->pos.start.y / GRID_MINI);
// 	// printf("find wall, x= %d and y= %d\n", (int)ray.x, (int)ray.y);
// 	printf("distance = %.2lf\n", distance);
//     return (distance);
// } 
