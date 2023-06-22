/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:41:02 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/22 17:54:31 by thmeyer          ###   ########.fr       */
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

static void	draw_wall(t_cub *cub, int column, int line, int max)
{
	int			side;
	double		wall_height;
	t_vector	mod;

	(void) max;
	(void) line;
	side = check_side_wall(cub, column);
	if (line == 0)
		wall_height = max;
	else
		wall_height = max - line;
	mod.x = fmod(cub->p->ray[column]->wall.x, GRID_MINI);
	mod.y = fmod(cub->p->ray[column]->wall.y, GRID_MINI);
	while (line < max)
	{
		if (side == 1)
			// put_pixel(&cub->imgs->back, column, line, get_pixel(cub->north, mod.x, line));
			put_pixel(&cub->imgs->back, column, line, get_pixel(cub->north, mod.x, line));
			// put_pixel(&cub->imgs->back, column, line, 0xBB33FF); // purple NORTH
		if (side == 2)
			put_pixel(&cub->imgs->back, column, line, get_pixel(cub->north, mod.x, line));
			// put_pixel(&cub->imgs->back, column, line, 0xFFB533); // yellow SOUTH
		if (side == 3)
			// put_pixel(&cub->imgs->back, column, line, get_pixel(cub->north, mod.x, line));
			put_pixel(&cub->imgs->back, column, line, 0x3336FF); // blue WEST
		if (side == 4)
			// put_pixel(&cub->imgs->back, column, line, get_pixel(cub->north, mod.y * cub->north.width, line));
			put_pixel(&cub->imgs->back, column, line, 0xFF33AC); // pink EAST
		line++;
	}
}

void	generate_3d(t_cub *cub)
{
	double	wall_height;
	double	distance;
	double	margin;
	int		ray;

	if (cub->imgs->back.img)
		mlx_destroy_image(cub->mlx, cub->imgs->back.img);
	cub->imgs->back.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->imgs->back.addr = mlx_get_data_addr(cub->imgs->back.img, \
	&cub->imgs->back.bits_per_pixel, &cub->imgs->back.line_length, \
	&cub->imgs->back.endian);
	ray = -1;
	put_floor_and_ceiling(cub);
	while (cub->p->ray[++ray])
	{
		distance = fix_fisheye(cub, ray);
		wall_height = WIN_HEIGHT / distance * 1.5;
		margin = (WIN_HEIGHT - wall_height) / 2;
		if (margin > 0 && margin < WIN_HEIGHT)
			draw_wall(cub, ray, margin, margin + wall_height - 1);
		else
			draw_wall(cub, ray, 0, WIN_HEIGHT);
	}
}
