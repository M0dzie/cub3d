/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:41:02 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/17 22:02:58 by thmeyer          ###   ########.fr       */
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

static void	draw_wall(t_cub *cub, int x, int y, int max)
{
	// if (check_side_wall(cub, x) == 1)
	// 	printf("NORTH\n");
	// if (check_side_wall(cub, x) == 2)
	// 	printf("SOUTH\n");
	// if (check_side_wall(cub, x) == 3)
	// 	printf("WEST\n");
	// if (check_side_wall(cub, x) == 4)
	// 	printf("EAST\n");
	int	side;

	side = check_side_wall(cub, x);
	while (y < max)
	{
		if (side == 1)
			put_pixel(&cub->imgs->back, x, y, 0xBB33FF); // purple NORTH
		if (side == 2)
			put_pixel(&cub->imgs->back, x, y, 0xFFB533); // yellow SOUTH
		if (side == 3)
			put_pixel(&cub->imgs->back, x, y, 0x3336FF); // blue WEST
		if (side == 4)
			put_pixel(&cub->imgs->back, x, y, 0xFF33AC); // pink EAST
		y++;
	}
}

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
		wall_height = WIN_HEIGHT / distance;
		margin = (WIN_HEIGHT - wall_height) / 2;
		if (margin > 0 && margin < WIN_HEIGHT)
			draw_wall(cub, x, margin, margin + wall_height - 1);
		else
			draw_wall(cub, x, 0, WIN_HEIGHT);
	}
}