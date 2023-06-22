/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:41:02 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/22 16:00:52 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

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

static void	draw_wall(t_cub *cub, int x, int line, int max)
{
	int	side;

	side = check_side_wall(cub, x);
	while (line < max)
	{
		if (side == 1)
			put_pixel(&cub->imgs->back, x, line, 0xBB33FF); // purple NORTH
		if (side == 2)
			put_pixel(&cub->imgs->back, x, line, 0xFFB533); // yellow SOUTH
		if (side == 3)
			put_pixel(&cub->imgs->back, x, line, 0x3336FF); // blue WEST
		if (side == 4)
			put_pixel(&cub->imgs->back, x, line, 0xFF33AC); // pink EAST
		line++;
	}
}

// static void	draw_wall(t_cub *cub, int x, int line, int max)
// {
// 	int			side;
// 	// double		wall_height;
// 	t_vector	mod;

// 	(void) max;
// 	(void) line;
// 	side = check_side_wall(cub, x);
// 	// if (line == 0)
// 	// 	wall_height = max;
// 	// else
// 	// 	wall_height = max - line;
// 	mod.x = fmod(cub->p->ray[x]->wall.x, GRID_MINI);
// 	mod.y = fmod(cub->p->ray[x]->wall.y, GRID_MINI);
// 	// put_pixel(&cub->imgs->back, x, line, get_pixel(cub->north, mod.x * cub->north.width, line));
// 	// while (line < max)
// 	// {
// 	// 	if (side == 1)
// 	// 		put_pixel(&cub->imgs->back, x, line, 0xBB33FF); // purple NORTH
// 	// 	if (side == 2)
// 	// 		put_pixel(&cub->imgs->back, x, line, 0xFFB533); // yellow SOUTH
// 	// 	if (side == 3)
// 	// 		put_pixel(&cub->imgs->back, x, line, 0x3336FF); // blue WEST
// 	// 	if (side == 4)
// 	// 		put_pixel(&cub->imgs->back, x, line, 0xFF33AC); // pink EAST
// 	// 	line++;
// 	// }
// 	for (int i = WIN_WIDTH / 2 - cub->north.width / 2; i < WIN_WIDTH / 2 + cub->north.width / 2; i++)
// 	{
// 		int j = WIN_HEIGHT / 2 - cub->north.height / 2;
// 		while (j < WIN_HEIGHT / 2 + cub->north.height / 2)
// 		{
// 			put_pixel(&cub->imgs->back, i, j, get_pixel(cub->north, i, j));
// 			// put_pixel(&cub->imgs->back, i, j, get_pixel(cub->north, \
// 			// fmod(i, GRID_MINI) * cub->north.width, fmod(j, GRID_MINI) * cub->north.height));
// 			j++;
// 		}
// 	}
// }

void	generate_3d(t_cub *cub)
{
	double	wall_height;
	double	distance;
	double	margin;
	int		x;

	if (cub->imgs->back.img)
		mlx_destroy_image(cub->mlx, cub->imgs->back.img);
	cub->imgs->back.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->imgs->back.addr = mlx_get_data_addr(cub->imgs->back.img, &cub->imgs->back.bits_per_pixel, &cub->imgs->back.line_length, &cub->imgs->back.endian);
	x = -1;
	put_floor_and_ceiling(cub);
	while (cub->p->ray[++x])
	{
		distance = fix_fisheye(cub, x);
		wall_height = WIN_HEIGHT / distance * 1.5;
		margin = (WIN_HEIGHT - wall_height) / 2;
		if (margin > 0 && margin < WIN_HEIGHT)
			draw_wall(cub, x, margin, margin + wall_height - 1);
		else
			draw_wall(cub, x, 0, WIN_HEIGHT);
	}
}
