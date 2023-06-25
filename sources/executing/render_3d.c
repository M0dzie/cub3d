/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:41:02 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/26 00:38:45 by mehdisapin       ###   ########.fr       */
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
			put_pixel(&cub->imgs->game, x, y, cub->roof);
		while (++y < WIN_HEIGHT)
			put_pixel(&cub->imgs->game, x, y, cub->floor);
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
			put_pixel(&cub->imgs->game, column, y + line, get_pixel(cub->north, mod.x, y));
			// put_pixel(&cub->imgs->back, column, y + line, get_pixel(cub->north, percent.x, line, wall_height));
			// put_pixel(&cub->imgs->back, column, y + line, 0xBB33FF); // purple NORTH
		if (side == 2)
			// put_pixel(&cub->imgs->back, column, y + line, get_pixel(cub->north, mod.x, ine));
			put_pixel(&cub->imgs->game, column, y + line, 0xFFB533); // yellow SOUTH
		if (side == 3)
			// put_pixel(&cub->imgs->back, column, y + line, get_pixel(cub->north, mod.x, line));
			put_pixel(&cub->imgs->game, column, y + line, 0x3336FF); // blue WEST
		if (side == 4)
			// put_pixel(&cub->imgs->back, column, y + line, get_pixel(cub->north, mod.y * cub->north.width, line));
			put_pixel(&cub->imgs->game, column, y + line, 0xFF33AC); // pink EAST
		y++;
		// line++;
	}
}

void	generate_3d(t_cub *cub)
{
	// double	wall_height;
	double	distance;
	// double	margin;
	int		ray;
	int		i;
	(void)draw_wall;
	(void)put_floor_and_ceiling;

	ray = -1;
	// put_floor_and_ceiling(cub);
	while (cub->p->ray[++ray])
	{
		// distance = fix_fisheye(cub, ray);
		// wall_height = WIN_HEIGHT / distance * 1.2;
		// margin = (WIN_HEIGHT - wall_height) / 2;

		cub->p->pos_3d.x = cub->p->pos.start.x / GRID_MINI + 0.5;
		cub->p->pos_3d.y = cub->p->pos.start.y / GRID_MINI + 0.5;

		cub->p->ray[ray]->coef = ray * 2 / WIN_WIDTH - 1;
		cub->p->ray[ray]->dir.x = cub->p->dir.x + cub->p->fov.y * cub->p->ray[ray]->coef;
		cub->p->ray[ray]->dir.y = cub->p->dir.y + cub->p->fov.x * cub->p->ray[ray]->coef;

		// temp to cast position into int
		int mapX = (int)cub->p->pos_3d.x;
		int mapY = (int)cub->p->pos_3d.y;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		
		 //length of ray from one x or y-side to next x or y-side
		cub->p->ray[ray]->delta.x = fabs(1 / cub->p->ray[ray]->dir.x);
		cub->p->ray[ray]->delta.y = fabs(1 / cub->p->ray[ray]->dir.y);
		
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (cub->p->ray[ray]->dir.x < 0)
		{
			stepX = -1;
			sideDistX = (cub->p->pos_3d.x - mapX) * cub->p->ray[ray]->delta.x;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - cub->p->pos_3d.x) * cub->p->ray[ray]->delta.x;
		}
		if (cub->p->ray[ray]->dir.y < 0)
		{
			stepY = -1;
			sideDistY = (cub->p->pos_3d.y - mapY) * cub->p->ray[ray]->delta.y;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - cub->p->pos_3d.y) * cub->p->ray[ray]->delta.y;
		}

		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += cub->p->ray[ray]->delta.x;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += cub->p->ray[ray]->delta.y;
				mapY += stepY;
				side = 1;
			}
			if (cub->map->array[mapY][mapX] == '1') 
				hit = 1;
		}
		if (side == 0)
			distance = (mapX - cub->p->pos_3d.x + (1 - stepX) / 2) / cub->p->ray[ray]->dir.x;
		else
			distance = (mapY - cub->p->pos_3d.y + (1 - stepY) / 2) / cub->p->ray[ray]->dir.y;

		int wall_height = (int)(WIN_HEIGHT / distance);
		
		(void)side;

		int drawStart = -wall_height / 2 + WIN_HEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = wall_height / 2 + WIN_HEIGHT / 2;
		if(drawEnd >= WIN_HEIGHT)
			drawEnd = WIN_HEIGHT - 1;

		double wall;
		if (side == 0)
			wall = cub->p->pos_3d.y + distance * cub->p->ray[ray]->dir.y;
		else
			wall = cub->p->pos_3d.x + distance * cub->p->ray[ray]->dir.x;
		wall -= floor(wall);

		// x coordinate on the texture
		int texX = (int)(wall * (double)cub->north.width);
		if (side == 0 && cub->p->ray[ray]->dir.x > 0)
			texX = cub->north.width - texX - 1;
		if (side == 1 && cub->p->ray[ray]->dir.y < 0)
			texX = cub->north.width - texX - 1;

		// How much to increase the texture coordinate perscreen pixel
		double step = 1.0 * cub->north.height / wall_height;

		// Starting texture coordinate
		double texPos = (drawStart - WIN_HEIGHT / 2 + wall_height / 2) * step;

		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (cub->north.height - 1);
			texPos += step;

			// define which texture
			int color = cub->north.px[cub->north.height * texY + texX];

			put_pixel(&cub->imgs->game, (int)WIN_WIDTH - ray, y, color);
		}
		if (drawEnd < 0)
			drawEnd = WIN_HEIGHT; //becomes < 0 when the integer overflows

		//draw the floor from drawEnd to the bottom of the screen
		i = drawEnd;
		while (++i < WIN_HEIGHT)
		{
			put_pixel(&cub->imgs->game, (int)WIN_WIDTH - ray, i, cub->floor);
			put_pixel(&cub->imgs->game, (int)WIN_WIDTH - ray, (int)WIN_HEIGHT - i, cub->roof);
		}
	// 	if (margin > 0 && margin < WIN_HEIGHT)
	// 		draw_wall(cub, ray, margin, wall_height);
	// 	else
	// 		draw_wall(cub, ray, 0, WIN_HEIGHT);
	}
}
