/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:41:02 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/21 15:37:42 by mehdisapin       ###   ########.fr       */
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

static void	draw_wall(t_cub *cub, int x, int y, int max, t_ray_map *ray, double wall_height, int margin)
{
	(void)wall_height;
	(void)ray;
	(void)margin;
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
		// if (side == NORTH)
		// 	// put_pixel(&cub->imgs->back, x, y, 0xBB33FF); // purple NORTH
		// 	wall_side = cub->north;
		// if (side == SOUTH)
		// 	// put_pixel(&cub->imgs->back, x, y, 0xFFB533); // yellow SOUTH
		// 	wall_side = cub->south;
		// if (side == 3)
		// 	// put_pixel(&cub->imgs->back, x, y, 0x3336FF); // blue WEST
		// 	wall_side = cub->west;
		// if (side == 4)
		// 	// put_pixel(&cub->imgs->back, x, y, 0xFF33AC); // pink EAST
		// 	wall_side = cub->east;

		int color = wall_side.px[(int)(((wall_side.height) * 1)) + (cub->north.height * i)];

		put_pixel(&cub->imgs->back, x, y, color);
		if ((y - margin) > (wall_height / (double)cub->north.height * i))
			i++;
		y++;
	}
}

void	generate_3d(t_cub *cub)
{
	double	wall_height;
	double	distance;
	double	margin;
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
	while (cub->p->ray[++x])
	{
		distance = fix_fisheye(cub, x);
		wall_height = WIN_HEIGHT / distance;
		margin = (WIN_HEIGHT - wall_height) / 2;

		// if (cub->p->ray[x]->side == ANGLE)
		int mapX = (cub->p->ray[x]->wall.x / GRID_MINI) + 0.5;
		int mapY = (cub->p->ray[x]->wall.y / GRID_MINI);

		double doubleMapX = (cub->p->ray[x]->wall.x / GRID_MINI) + 0.5;
		double doubleMapY = (cub->p->ray[x]->wall.y / GRID_MINI);
		(void)mapX;
		(void)mapY;
		(void)doubleMapX;
		(void)doubleMapY;

		if (x == 1279)
		{
			// printf("%d/ \nmapX: %d     mapY: %d\ndoubleMapX: %f    doubleMapY: %f\nratioWall: %f\n\n", x, mapX, mapY, doubleMapX, doubleMapY, doubleMapX - mapX);
			// printf("%d/\nwallHeight%f\n", x, wall_height);

		}
		// printf("size wall: %f\n", wall_height);

		if (margin > 0 && margin < WIN_HEIGHT)
			draw_wall(cub, x, margin, margin + wall_height - 1, cub->p->ray[x], wall_height, margin);
		else
			draw_wall(cub, x, 0, WIN_HEIGHT, cub->p->ray[x], wall_height, margin);
	}
	// printf("nbWall: %d\n", nbWall);
}
