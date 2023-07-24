/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:41:02 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/24 13:33:39 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

static int	check_side_wall(t_cub *cub, int x)
{
	if (cub->p->ray[x]->side == NORTH)
		return (1);
	if (cub->p->ray[x]->side == SOUTH)
		return (2);
	if (cub->p->ray[x]->side == WEST)
		return (3);
	if (cub->p->ray[x]->side == EAST)
		return (4);
	return (0);
}

static void	draw_wall(t_cub *cub, int x, int y, int max, t_ray_map *ray, int px_column)
{
	(void)ray;
	(void)px_column;
	int	side;
	t_xpm	wall_side;
	int		i;
	(void)side;

	side = check_side_wall(cub, x);
	if (ray->side == EAST)
		wall_side = cub->east;
	else if (ray->side == WEST)
		wall_side = cub->west;
	else if (ray->side == SOUTH)
		wall_side = cub->south;
	else
		wall_side = cub->north;
	// i = -cub->p->ray[x]->margin;
	i = 0;
	while (y < max)
	{
		int color = wall_side.px[wall_side.height * i + px_column];
		// int color = 0x000362fc;
		(void)wall_side;
		put_pixel(&cub->imgs->back, x, y, color);
		if ((y - cub->p->ray[x]->margin) > (cub->p->ray[x]->wall_height / (double)cub->north.height * i))
			i++;
		y++;
	}
}

void	calcul_ray(t_cub *cub)
{
	int	ray;
	int tmpRatioX;
	int tmpRatioY;

	ray = -1;
	cub->p->nb_wall = 0;
	tmpRatioX = 0;
	tmpRatioY = 0;
	while (cub->p->ray[++ray])
	{
		// double oldDistance = fix_fisheye(cub, ray);
		// double oldWall_height = WIN_HEIGHT / oldDistance;
		// double oldMargin = (WIN_HEIGHT - oldWall_height) / 2;

		cub->p->ray[ray]->distance = fix_fisheye(cub, ray);
		cub->p->ray[ray]->wall_height = WIN_HEIGHT / cub->p->ray[ray]->distance;
		cub->p->ray[ray]->margin = (WIN_HEIGHT - cub->p->ray[ray]->wall_height) / 2;

		// cub->p->ray[ray]->distance = new_distance_to_wall(cub, cub->p->pos.coef_ns, 1, 0);
		// cub->p->ray[ray]->wall_height = WIN_HEIGHT / cub->p->ray[ray]->distance;
		// cub->p->ray[ray]->wall_height = WIN_HEIGHT / cub->p->ray[ray]->distance * GRID_MINI;


		cub->p->ray[ray]->map.x = (cub->p->ray[ray]->wall.x / GRID_MINI) + 0.5;
		cub->p->ray[ray]->map.y = (cub->p->ray[ray]->wall.y / GRID_MINI);

		cub->p->ray[ray]->index_wall = cub->p->nb_wall;

		// printf("wall: %d   distance: %f   mapX: %f   mapY: %f   (int)mapX: %d   (int)mapY: %d\n", ray, cub->p->ray[ray]->distance, cub->p->ray[ray]->map.x, cub->p->ray[ray]->map.y, (int)cub->p->ray[ray]->map.x, (int)cub->p->ray[ray]->map.y);

		// if (ray == 0 || ray == 639 || ray == 1279)
		// {
		// 	// printf("old wall: %d   distance: %f   wall_height %f   margin: %f\n", ray, oldDistance, oldWall_height, oldMargin);
		// 	printf("new wall: %d   distance: %f   wall_height %f   margin: %f   wallX: %f   wallY: %f\n", ray, cub->p->ray[ray]->distance, cub->p->ray[ray]->wall_height, cub->p->ray[ray]->margin, cub->p->ray[ray]->wall.x, cub->p->ray[ray]->wall.y);
		// 	printf("\n");
		// }

		if ((int)cub->p->ray[ray]->map.x != tmpRatioX || (int)cub->p->ray[ray]->map.y != tmpRatioY || ray == WIN_WIDTH - 1 || ray == 0)
		{
			tmpRatioX = cub->p->ray[ray]->map.x;
			tmpRatioY = cub->p->ray[ray]->map.y;
			if (ray != 0 && ray != WIN_WIDTH - 1)
				cub->p->nb_wall++;
		}
	}
	// printf("\n");
}

int	get_middle(t_cub *cub, int index_wall)
{
	int	middle;
	int	i;

	i = -1;
	middle = 0;
	while (++i < index_wall)
		middle += cub->p->wall[i].width;
	middle += cub->p->wall[i].width / 2;
	return (middle);
}

int	calcul_wall_bloc(t_cub *cub)
{
	int	ray;
	int	tmpWidth = 0;
	int tmpRatioX = 0;
	int tmpRatioY = 0;
	int	tmpIndex = 0;
	(void)ray;
	(void)tmpWidth;
	(void)tmpIndex;

	if (cub->p->wall)
		free(cub->p->wall);
	cub->p->wall = ft_calloc(cub->p->nb_wall + 1, sizeof(t_wall));
	if (!cub->p->wall)
		return (printf("crash malloc\n"), -1);
	ray = -1;
	int index_wall = -1;
	while (cub->p->ray[++ray])
	{
		if (((int)cub->p->ray[ray]->map.x != tmpRatioX || (int)cub->p->ray[ray]->map.y != tmpRatioY || ray == 0 || ray == WIN_WIDTH - 1))
		{
			// use map x or y depending of side wall
			int middle_wall = get_middle(cub, index_wall);
			if (ray != 0)
			{
				cub->p->wall[index_wall].width = tmpWidth;
				middle_wall = get_middle(cub, index_wall);
				// printf("%d\n", get_middle(cub, index_wall));
				if (cub->p->ray[middle_wall]->side == NORTH)
				{
					cub->p->wall[index_wall].percent_end = 100 - (cub->p->ray[ray - 1]->map.x - (int)cub->p->ray[ray - 1]->map.x) * 100;
					cub->p->wall[index_wall].side = 1;
					// printf("%d/   NORTH: %d\n", ray, cub->p->ray[ray]->side);
				}
				else if (cub->p->ray[middle_wall]->side == SOUTH)
				{
					cub->p->wall[index_wall].percent_end = (cub->p->ray[ray - 1]->map.x - (int)cub->p->ray[ray - 1]->map.x) * 100;
					cub->p->wall[index_wall].side = 2;
					// printf("%d/   SOUTH: %d\n", ray, cub->p->ray[ray]->side);
				}
				else if (cub->p->ray[middle_wall]->side == EAST)
				{
					cub->p->wall[index_wall].percent_end = (cub->p->ray[ray - 1]->map.y - (int)cub->p->ray[ray - 1]->map.y) * 100;
					cub->p->wall[index_wall].side = 3;
					// printf("%d/   EAST: %d\n", ray, cub->p->ray[ray]->side);
				}
				else if (cub->p->ray[middle_wall]->side == WEST)
				{
					cub->p->wall[index_wall].percent_end = (cub->p->ray[ray - 1]->map.y - (int)cub->p->ray[ray - 1]->map.y) * 100;
					cub->p->wall[index_wall].side = 4;
					// printf("%d/   WEST: %d\n", ray, cub->p->ray[ray]->side);
				}
			}
			if (ray == WIN_WIDTH - 1)
				break;
			tmpWidth = 0;
			index_wall++;
			if (cub->p->ray[middle_wall]->side == NORTH)
				cub->p->wall[index_wall].percent_start = 100 - (cub->p->ray[ray]->map.x - (int)cub->p->ray[ray]->map.x) * 100;
			if (cub->p->ray[middle_wall]->side == SOUTH)
				cub->p->wall[index_wall].percent_start = (cub->p->ray[ray]->map.x - (int)cub->p->ray[ray]->map.x) * 100;
			else if (cub->p->ray[middle_wall]->side == EAST)
				cub->p->wall[index_wall].percent_start = ((cub->p->ray[ray]->map.y - (int)cub->p->ray[ray]->map.y) * 100);
			else if (cub->p->ray[middle_wall]->side == WEST)
				cub->p->wall[index_wall].percent_start = (cub->p->ray[ray]->map.y - (int)cub->p->ray[ray]->map.y) * 100;
			tmpRatioX = cub->p->ray[ray]->map.x;
			tmpRatioY = cub->p->ray[ray]->map.y;
		}
		tmpWidth++;
	}
	// for (int i = 0; i <= cub->p->nb_wall; i++)
	// {
	// 	if (cub->p->wall[i].side == 1)
	// 	{
	// 		double tmp = cub->p->wall[i].percent_start;
	// 		cub->p->wall[i].percent_start = cub->p->wall[i].percent_end;
	// 		cub->p->wall[i].percent_end = tmp;
	// 	}
	// }
	return (0);
}

void	generate_3d(t_cub *cub)
{
	int		x;

	(void)draw_wall;
	(void)x;
	
	if (cub->imgs->back.img)
		mlx_destroy_image(cub->mlx, cub->imgs->back.img);
	cub->imgs->back.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->imgs->back.addr = mlx_get_data_addr(cub->imgs->back.img, &cub->imgs->back.bits_per_pixel, &cub->imgs->back.line_length, &cub->imgs->back.endian);
	x = -1;
	put_floor_and_ceiling(cub);

	calcul_ray(cub);
	calcul_wall_bloc(cub);

	int tmp_index = 0;
	int tmp_wall = 0;
	(void)tmp_index;
	(void)tmp_wall;
	(void)x;
	while (cub->p->ray[++x])
	{
		double	show_width = cub->p->wall[cub->p->ray[x]->index_wall].width;
		double	full_width = cub->p->wall[cub->p->ray[x]->index_wall].width * 100 / (cub->p->wall[cub->p->ray[x]->index_wall].percent_end - cub->p->wall[cub->p->ray[x]->index_wall].percent_start);
		double	percent_show = show_width / full_width * 100;
		(void)percent_show;
		double	ratio_percent = 128 / full_width;

		(void)show_width;
		(void)full_width;
		(void)ratio_percent;

		if (tmp_wall != cub->p->ray[x]->index_wall)
		{
			tmp_wall = cub->p->ray[x]->index_wall;
			tmp_index = 0;
		}

		// int	px_line = (128 * ((cub->p->wall[cub->p->ray[x]->index_wall].percent_start) / 100)) + (tmp_index * ratio_percent);
		int	px_line = 128;

		if (cub->p->ray[x]->margin > 0 && cub->p->ray[x]->margin < WIN_HEIGHT)
			draw_wall(cub, x, cub->p->ray[x]->margin, cub->p->ray[x]->margin + cub->p->ray[x]->wall_height - 1, cub->p->ray[x], px_line);  // temporary
		else
			draw_wall(cub, x, 0, WIN_HEIGHT, cub->p->ray[x], px_line);  // temporary
		tmp_index++;
	}
	// for (int i = 0; i <= cub->p->nb_wall; i++)
	// {
	// 	printf("wall %d/   side: %d   width: %d   percent_start: %f   percent_end: %f\n", i, cub->p->wall[i].side, cub->p->wall[i].width, cub->p->wall[i].percent_start, cub->p->wall[i].percent_end);
	// }
	// printf("\n");
}
