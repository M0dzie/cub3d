/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:41:02 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/22 15:04:13 by mehdisapin       ###   ########.fr       */
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
	if (ray->side == EAST)
		wall_side = cub->east;
	else if (ray->side == WEST)
		wall_side = cub->west;
	else if (ray->side == SOUTH)
		wall_side = cub->south;
	else
		wall_side = cub->north;
	while (y < max)
	{
		int color = wall_side.px[(wall_side.height) * i + tex_line];
		ray->tex.color = wall_side.px[wall_side.height * ray->tex.tex_y + ray->tex.tex_x];
		put_pixel(&cub->imgs->back, x, y, color);
		if ((y - cub->p->ray[x]->margin) > (cub->p->ray[x]->wall_height / (double)cub->north.height * i))
			i++;
		y++;
	}
}

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
			// printf("wall %d/   indexWall: %d   %f   %d   %d\n", ray, cub->p->ray[ray]->index_wall, cub->p->ray[ray]->map.x, tmpRatioX, tmpRatioY);
			if (ray == WIN_WIDTH - 1)
				break ;
			tmpRatioX = cub->p->ray[ray]->map.x;
			tmpRatioY = cub->p->ray[ray]->map.y;
			if (ray != 0)
				cub->p->nb_wall++;
		}
		tmpWidth++;
	}
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

	// if (cub->p->wall)
	// 	free(cub->p->wall);
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
			if (ray != 0)
			{
				// if (cub->p->ray[0]->side == NORTH || cub->p->ray[0]->side == SOUTH)
				// 	cub->p->wall[index_wall].percent_end = (cub->p->ray[ray - 1]->map.x - (int)cub->p->ray[ray - 1]->map.x) * 100;
				// else if (cub->p->ray[0]->side == EAST || cub->p->ray[0]->side == WEST)
				// 	cub->p->wall[index_wall].percent_end = (cub->p->ray[ray - 1]->map.y - (int)cub->p->ray[ray - 1]->map.y) * 100;
				cub->p->wall[index_wall].percent_end = (cub->p->ray[ray - 1]->map.x - (int)cub->p->ray[ray - 1]->map.x) * 100;

				cub->p->wall[index_wall].width = tmpWidth;
			}
			if (ray == WIN_WIDTH - 1)
				break;
			tmpWidth = 0;
			index_wall++;
			if (cub->p->ray[0]->side == NORTH || cub->p->ray[0]->side == SOUTH)
				cub->p->wall[index_wall].percent_start = (cub->p->ray[ray]->map.x - (int)cub->p->ray[ray]->map.x) * 100;
			else if (cub->p->ray[0]->side == EAST || cub->p->ray[0]->side == WEST)
				cub->p->wall[index_wall].percent_start = (cub->p->ray[ray]->map.y - (int)cub->p->ray[ray]->map.y) * 100;
			tmpRatioX = cub->p->ray[ray]->map.x;
			tmpRatioY = cub->p->ray[ray]->map.y;
			
			// if (ray == 0)
			// 	printf("%f\n", cub->p->wall[index_wall].percent_start);
		}
		tmpWidth++;
	}
	return (0);
}

void	generate_3d(t_cub *cub)
{
	int		x;

	(void)draw_wall;
	
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

		int	px_line = (128 * ((cub->p->wall[cub->p->ray[x]->index_wall].percent_start) / 100)) + (tmp_index * ratio_percent);
		if (x % 10 == 0)
		// if (x == 800)
		{
			// printf("ray: %d/   index_wall: %d    px_line: %d\n", x, cub->p->ray[x]->index_wall, (int)(px_line));
			// printf("show: %f    full_width: %f\n", show_width, full_width);
			// printf("ratio_percent show: %f\n", ratio_percent);
		}

		// px_line = 50;
		if (cub->p->ray[x]->margin > 0 && cub->p->ray[x]->margin < WIN_HEIGHT)
			draw_wall(cub, x, cub->p->ray[x]->margin, cub->p->ray[x]->margin + cub->p->ray[x]->wall_height - 1, cub->p->ray[x], px_line);  // temporary
		else
			draw_wall(cub, x, 0, WIN_HEIGHT, cub->p->ray[x], px_line);  // temporary
		tmp_index++;
	}
}
