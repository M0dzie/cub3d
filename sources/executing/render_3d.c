/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:41:02 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/23 15:31:34 by thmeyer          ###   ########.fr       */
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

double	get_percent_face(double face)
{
	double	res;

	res = face - (int)face;
	return (res);
}

static void	draw_wall(t_cub *cub, int column, int line, double wall_height)
{
	int			y;
	int			side;
	t_vector	mod;
	t_vector	percent;

	(void) percent;
	(void) mod;
	y = 0; // c'est le point 0 de la texture, pour que je cherche le pixel depuis le tout debut
	if (line != 0)
		wall_height = wall_height + line; // pour retablir la bonne hauteur du mur avec la boucle while
	side = check_side_wall(cub, column);
	// mod.x = fmod(cub->p->ray[column]->wall.x, wall_height);
	// mod.y = fmod(cub->p->ray[column]->wall.y, wall_height);
	mod.x = fmod(cub->p->ray[column]->wall.x, GRID_MINI);
	mod.y = fmod(cub->p->ray[column]->wall.y, GRID_MINI);
	percent.x = get_percent_face(cub->p->ray[column]->wall.x); // ca c'est des calculs pour la methode de nico (a voir lundi)
	percent.y = get_percent_face(cub->p->ray[column]->wall.y);
	while (y + line < wall_height)
	{
		if (side == 1)
			put_pixel(&cub->imgs->back, column, y + line, get_pixel(cub->north, mod.x, y));
			// put_pixel(&cub->imgs->back, column, y + line, get_pixel(cub->north, percent.x, line, wall_height));
			// put_pixel(&cub->imgs->back, column, y + line, 0xBB33FF); // purple NORTH
		if (side == 2)
			// put_pixel(&cub->imgs->back, column, y + line, get_pixel(cub->north, mod.x, ine));
			put_pixel(&cub->imgs->back, column, y + line, 0xFFB533); // yellow SOUTH
		if (side == 3)
			// put_pixel(&cub->imgs->back, column, y + line, get_pixel(cub->north, mod.x, line));
			put_pixel(&cub->imgs->back, column, y + line, 0x3336FF); // blue WEST
		if (side == 4)
			// put_pixel(&cub->imgs->back, column, y + line, get_pixel(cub->north, mod.y * cub->north.width, line));
			put_pixel(&cub->imgs->back, column, y + line, 0xFF33AC); // pink EAST
		y++;
		// line++;
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
			draw_wall(cub, ray, margin, wall_height);
		else
			draw_wall(cub, ray, 0, WIN_HEIGHT);
	}
}
