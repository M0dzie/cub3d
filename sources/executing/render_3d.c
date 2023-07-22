/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:41:02 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/22 02:26:38 by mehdisapin       ###   ########.fr       */
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

static void	draw_wall(t_cub *cub, int x, int y, int max, t_ray_map *ray, int tex_line)
{
	(void)ray;
	(void)tex_line;
	int	side;
	t_xpm	wall_side;
	int		i;
	(void)side;

	side = check_side_wall(cub, x);
	i = 0;
	wall_side = cub->north;
	// if (ray->side == EAST)
	// 	wall_side = cub->east;
	// else if (ray->side == WEST)
	// 	wall_side = cub->west;
	// else if (ray->side == SOUTH)
	// 	wall_side = cub->south;
	// else if (ray->side == NORTH)
	// 	wall_side = cub->north;
	while (y < max)
	{
		int color = wall_side.px[(int)(((wall_side.height) * tex_line)) + (cub->north.height * i)];

		put_pixel(&cub->imgs->back, x, y, color);
		if ((y - cub->p->ray[x]->margin) > (cub->p->ray[x]->wall_height / (double)cub->north.height * i))
			i++;
		y++;
	}
}

// static void	draw_wall_bloc(t_cub *cub, int x, int y, int max, int mapX, int mapY, double doubleMapX, double doubleMapY, double wall_height)
// {
// 	int	side;
// 	t_xpm	wall_side;
// 	int		i;
// 	(void)side;

// 	side = check_side_wall(cub, x);
// 	i = 0;
// 	wall_side = cub->north;
// 	// if (ray->side == EAST)
// 	// 	wall_side = cub->east;
// 	// else if (ray->side == WEST)
// 	// 	wall_side = cub->west;
// 	// else if (ray->side == SOUTH)
// 	// 	wall_side = cub->south;
// 	// else if (ray->side == NORTH)
// 	// 	wall_side = cub->north;
// 	while (y < max)
// 	{
// 		int color = wall_side.px[(int)(((wall_side.height) * 1)) + (cub->north.height * i)];

// 		put_pixel(&cub->imgs->back, x, y, color);
// 		if ((y - margin) > (wall_height / (double)cub->north.height * i))
// 			i++;
// 		y++;
// 	}
// }

void	calcul_ray(t_cub *cub)
{
	int	ray;
	int	tmpWidth;
	// int tmpRatioY = ((cub->p->ray[0]->wall.y / GRID_MINI));
	// int tmpRatioX = tmpRatioY + 0.5;
	int tmpRatioY = 0;
	int tmpRatioX = 0;

	ray = -1;
	tmpWidth = 0;
	cub->p->nb_wall = 0;
	while (cub->p->ray[++ray])
	{
		cub->p->ray[ray]->distance = fix_fisheye(cub, ray);
		cub->p->ray[ray]->wall_height = WIN_HEIGHT / cub->p->ray[ray]->distance;
		cub->p->ray[ray]->margin = (WIN_HEIGHT - cub->p->ray[ray]->wall_height) / 2;

		// cub->p->ray[ray]->map_x = (cub->p->ray[ray]->wall.x / GRID_MINI) + 0.5;
		// cub->p->ray[ray]->map_y = (cub->p->ray[ray]->wall.y / GRID_MINI);

		// cub->p->ray[ray]->coord_wall.x = (cub->p->ray[ray]->wall.x / GRID_MINI) + 0.5;
		// cub->p->ray[ray]->coord_wall.y = (cub->p->ray[ray]->wall.y / GRID_MINI);

		cub->p->ray[ray]->map.x = (cub->p->ray[ray]->wall.x / GRID_MINI) + 0.5;
		cub->p->ray[ray]->map.y = (cub->p->ray[ray]->wall.y / GRID_MINI);
		
		cub->p->ray[ray]->index_wall = cub->p->nb_wall;
		if ((int)cub->p->ray[ray]->map.x != tmpRatioX || (int)cub->p->ray[ray]->map.y != tmpRatioY || ray == WIN_WIDTH - 1 || ray == 0)
		{
			// tmpWidth = 0;
			// printf("wall %d/   %f   %d   %d\n", cub->p->ray[ray]->index_wall, cub->p->ray[ray]->map.x, tmpRatioX, tmpRatioY);
			tmpRatioX = cub->p->ray[ray]->map.x;
			tmpRatioY = cub->p->ray[ray]->map.y;
			cub->p->nb_wall++;
		}
		tmpWidth++;
	}
}

int	calcul_wall_bloc(t_cub *cub)
{
	int	ray;
	int	tmpWidth = 0;
	// int tmpRatioX = ((cub->p->ray[0]->wall.x / GRID_MINI) + 0.5);
	// int tmpRatioY = ((cub->p->ray[0]->wall.y / GRID_MINI));
	int tmpRatioX = 0;
	int tmpRatioY = 0;
	int	tmpIndex = 0;
	(void)ray;
	(void)tmpWidth;
	(void)tmpIndex;

	// if (cub->p->wall)
	// 	free(cub->p->wall);
	cub->p->wall = ft_calloc(cub->p->nb_wall + 1, sizeof(t_wall));
	if (!cub->p->wall)
		return (printf("crash malloc\n"), -1);
	ray = -1;
	int index_wall = 0;
	(void)index_wall;
	// cub->p->wall[0].width = 0;
	// cub->p->wall[0].percent_start = cub->p->ray[0]->coord_wall.x;

	// if (cub->p->ray[0]->side == NORTH || cub->p->ray[0]->side == SOUTH)
	// {
	// 	// printf("wall: %d /  %f\n", cub->p->ray[0]->index_wall, (cub->p->ray[0]->coord_wall.x - cub->p->ray[0]->map_x) * 100);
	// }
	// else if (cub->p->ray[0]->side == EAST || cub->p->ray[0]->side == WEST)
	// {
	// 	// printf("wall: %d /  %f\n", cub->p->ray[0]->index_wall, (cub->p->ray[0]->coord_wall.y - cub->p->ray[0]->map_y) * 100);
	// }

	while (cub->p->ray[++ray])
	{
		// if ((int)cub->p->ray[ray]->map.x != tmpRatioX || (int)cub->p->ray[ray]->map.y != tmpRatioY || ray == WIN_WIDTH - 1 || ray == 0)
		// {
		// 	// tmpWidth = 0;
		// 	tmpRatioX = cub->p->ray[ray]->map.x;
		// 	tmpRatioY = cub->p->ray[ray]->map.y;
		// 	printf("wall %d/   %f   %d   %d\n", cub->p->ray[ray]->index_wall, cub->p->ray[ray]->map.x, tmpRatioX, tmpRatioY);
		// }

		if (ray == 0)
		{
			// cub->p->wall[index_wall].width = 0;
			cub->p->wall[index_wall].percent_start = (cub->p->ray[ray]->map.x - (int)cub->p->ray[ray]->map.x) * 100;
			tmpRatioX = cub->p->ray[ray]->map.x;
			tmpRatioY = cub->p->ray[ray]->map.y;
			// printf("wall %d/   %f   %d   %d\n", cub->p->ray[ray]->index_wall, cub->p->ray[ray]->map.x, tmpRatioX, tmpRatioY);
		}
		else if (ray == WIN_WIDTH - 1)
		{
			// use x or y depending of side wall
			cub->p->wall[index_wall].percent_end = (cub->p->ray[ray]->map.x - (int)cub->p->ray[ray]->map.x) * 100;
			cub->p->wall[index_wall].width = tmpWidth;
			tmpRatioX = cub->p->ray[ray]->map.x;
			tmpRatioY = cub->p->ray[ray]->map.y;
		}
		else if (((int)cub->p->ray[ray]->map.x != tmpRatioX || (int)cub->p->ray[ray]->map.y != tmpRatioY))
		{
			// use map x or y depending of side wall
			// printf("wall %d   %f\n", cub->p->ray[ray]->index_wall, cub->p->ray[ray]->map.x);
			// cub->p->wall[index_wall].percent_end = (cub->p->ray[ray - 1]->map.x - (int)cub->p->ray[ray - 1]->map.x) * 100;
			cub->p->wall[index_wall].percent_end = (cub->p->ray[ray - 1]->map.x - (int)cub->p->ray[ray - 1]->map.x) * 100;
			cub->p->wall[index_wall].width = tmpWidth;
			tmpWidth = 0;
			index_wall++;
			cub->p->wall[index_wall].percent_start = (cub->p->ray[ray]->map.x - (int)cub->p->ray[ray]->map.x) * 100;

			tmpRatioX = cub->p->ray[ray]->map.x;
			tmpRatioY = cub->p->ray[ray]->map.y;
		// 	cub->p->nb_wall++;
		}
		tmpWidth++;
	}
	return (0);
}

void	generate_3d(t_cub *cub)
{
	// double	wall_height;
	// double	distance;
	// double	margin;
	int		x;

	(void)draw_wall;
	
	if (cub->imgs->back.img)
		mlx_destroy_image(cub->mlx, cub->imgs->back.img);
	cub->imgs->back.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->imgs->back.addr = mlx_get_data_addr(cub->imgs->back.img, &cub->imgs->back.bits_per_pixel, &cub->imgs->back.line_length, &cub->imgs->back.endian);
	x = -1;
	put_floor_and_ceiling(cub);

	int nbWall = 0;
	(void)nbWall;

	// int tmpRatioX = (((cub->p->ray[0]->wall.x / GRID_MINI) + 0.5) - (int)((cub->p->ray[0]->wall.x / GRID_MINI) + 0.5)) * 1000;
	// int tmpRatioY = (((cub->p->ray[0]->wall.y / GRID_MINI) + 0.5) - (int)((cub->p->ray[0]->wall.y / GRID_MINI) + 0.5)) * 1000;
	// int tmpRatioX = ((cub->p->ray[0]->wall.x / GRID_MINI) + 0.5);
	// int tmpRatioY = ((cub->p->ray[0]->wall.y / GRID_MINI));

	// int tmpWidth = 0;
	// printf("tmpRatioX: %d   tmpRatioY: %d\n", tmpRatioX, tmpRatioY);

	calcul_ray(cub);
	calcul_wall_bloc(cub);

	int tmp_index = 0;
	(void)tmp_index;
	// printf("wall %d/  width: %d   percent_start: %f    percent_end: %f\n", tmp_index, cub->p->wall[tmp_index].width, cub->p->wall[tmp_index].percent_start, cub->p->wall[tmp_index].percent_end);

	// printf("nbWall: %d\n", cub->p->nb_wall);
	
	
	while (cub->p->ray[++x])
	{
		// distance = fix_fisheye(cub, x);
		// wall_height = WIN_HEIGHT / distance;
		// margin = (WIN_HEIGHT - wall_height) / 2;

		// int mapX = (cub->p->ray[x]->wall.x / GRID_MINI) + 0.5;
		// int mapY = (cub->p->ray[x]->wall.y / GRID_MINI);

		// double doubleMapX = (cub->p->ray[x]->wall.x / GRID_MINI) + 0.5;
		// double doubleMapY = (cub->p->ray[x]->wall.y / GRID_MINI);
		// (void)mapX;
		// (void)mapY;
		// (void)doubleMapX;
		// (void)doubleMapY;

		// if (mapX != tmpRatioX || mapY != tmpRatioY || x == WIN_WIDTH - 1)
		// {
		// 	// printf("X   %d/ %d\n", x, (int)((doubleMapX - mapX) * 1000));
		// 	printf("wall: %d    tmpWidth: %d\n", nbWall, tmpWidth);
		// 	// draw_wall(cub)
		// 	// draw_wall_bloc(cub, x, y, max, mapX, mapY, doubleMapX, doubleMapY, wall_height);
		// 	tmpWidth = 0;
		// 	tmpRatioX = mapX;
		// 	tmpRatioY = mapY;
		// 	nbWall++;
		// }
		// tmpWidth++;

		if (x == 0)
		{
			
		}

		double	show_width = cub->p->wall[cub->p->ray[x]->index_wall].width;
		double	full_width = cub->p->wall[cub->p->ray[x]->index_wall].width * 100 / (cub->p->wall[cub->p->ray[x]->index_wall].percent_end - cub->p->wall[cub->p->ray[x]->index_wall].percent_start);
		double	percent_show = show_width / full_width * 100;
		double	ratio_percent = percent_show / show_width;

		(void)show_width;
		(void)full_width;
		(void)ratio_percent;
		// if ((y - cub->p->ray[x]->margin) > (cub->p->ray[x]->wall_height / (double)cub->north.height * i))
		// 	i++;

		if (x == 0)
		{
			// printf("index wall: %d\n", cub->p->ray[x]->index_wall);
			// printf("ray 0/  show: %f    full_width: %f\n", show_width, full_width);
			// printf("ray 0/  percent show: %f\n", percent_show);
		}

		// int	px_line = 128 * ((cub->p->wall[cub->p->ray[x]->index_wall].percent_start + (x * ratio_percent)) / 100);
		int	px_line = 128 * ((cub->p->wall[cub->p->ray[x]->index_wall].percent_start) / 100);

		if (cub->p->ray[x]->margin > 0 && cub->p->ray[x]->margin < WIN_HEIGHT)
			draw_wall(cub, x, cub->p->ray[x]->margin, cub->p->ray[x]->margin + cub->p->ray[x]->wall_height - 1, cub->p->ray[x], px_line);  // temporary
		else
			draw_wall(cub, x, 0, WIN_HEIGHT, cub->p->ray[x], px_line);  // temporary
	}
	
}
