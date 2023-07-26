/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:41:02 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/26 22:40:26 by thmeyer          ###   ########.fr       */
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

int	check_side_wall(t_cub *cub, int x)
{
	(void)cub;
	(void)x;
	// if (cub->p->ray[x]->side == NORTH)
	// 	return (1);
	// if (cub->p->ray[x]->side == SOUTH)
	// 	return (2);
	// if (cub->p->ray[x]->side == WEST)
	// 	return (3);
	// if (cub->p->ray[x]->side == EAST)
	// 	return (4);
	return (0);
}

static int	get_texture_pixel(t_xpm tex, int x, int y)
{
	char	*dst;

	dst = tex.addr + (y * tex.line_length + x * (tex.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

static void	draw_wall(t_cub *cub, int x, int y, int max, t_ray_map *ray)
{
	t_xpm	tex;
	int tex_x;
	int tex_y;
	int tmp_y;

	if (ray->side == EAST)
	{
		tex = cub->east;
		tex_x = (cub->p->ray[x]->map.y - (int)cub->p->ray[x]->map.y) * tex.width;
	}
	else if (ray->side == WEST)
	{
		tex = cub->west;
		tex_x = (cub->p->ray[x]->map.y - (int)cub->p->ray[x]->map.y) * tex.width;
		tex_x = tex.width - tex_x;
	}
	else if (ray->side == SOUTH)
	{
		tex = cub->south;
		tex_x = (cub->p->ray[x]->map.x - (int)cub->p->ray[x]->map.x) * tex.width;
		tex_x = tex.width - tex_x;
	}
	else
	{
		tex = cub->north;
		tex_x = (cub->p->ray[x]->map.x - (int)cub->p->ray[x]->map.x) * tex.width;
	}		
	if (cub->p->ray[x]->wall_height > WIN_HEIGHT)
		tmp_y = fabs((max / 2) - (cub->p->ray[x]->wall_height / 2));
	else
		tmp_y = 0;
	while (y < max)
	{
		tex_y = tmp_y * (tex.height / cub->p->ray[x]->wall_height);
		int color = get_texture_pixel(tex, tex_x, tex_y);
		put_pixel(&cub->imgs->back, x, y, color);
		tmp_y++;
		y++;
	}
}

void	calcul_ray(t_cub *cub)
{
	int	ray;
	// int old_map_x;
	// int old_map_y;
	// int tmp_side;
	// (void)tmp_side;

	ray = -1;
	// cub->p->nb_wall = 0;
	// old_map_x = cub->p->ray[0]->wall.x / GRID_MINI;
	// old_map_y = cub->p->ray[0]->wall.y / GRID_MINI;
	// tmp_side = cub->p->ray[0]->side;
	while (cub->p->ray[++ray])
	{
		cub->p->ray[ray]->distance = fix_fisheye(cub, ray);
		cub->p->ray[ray]->wall_height = WIN_HEIGHT / cub->p->ray[ray]->distance;
		cub->p->ray[ray]->margin = (WIN_HEIGHT - cub->p->ray[ray]->wall_height) / 2;

		cub->p->ray[ray]->map.x = cub->p->ray[ray]->wall.x / GRID_MINI;
		cub->p->ray[ray]->map.y = cub->p->ray[ray]->wall.y / GRID_MINI;

		// cub->p->ray[ray]->index_wall = cub->p->nb_wall;
		
		// if (ray == 638 || ray == 639 || ray == 640)
		// 	printf("ray %d/   mapX: %f   mapY: %f\n", ray, cub->p->ray[ray]->map.x, cub->p->ray[ray]->map.y);

		// if ((old_map_x != (int)cub->p->ray[ray]->map.x || old_map_y != (int)cub->p->ray[ray]->map.y) || tmp_side != cub->p->ray[ray]->side || ray == WIN_WIDTH - 1)
		// {
		// 	/*printf("NEW WALL %d\t%dpx\toldX = %d\tnewX = %d\toldY = %d\tnewY = %d\toldSide = %d\tnewSide = %d\n", cub->p->nb_wall, 
		// 	ray, old_map_x, (int)cub->p->ray[ray]->map.x, old_map_y, (int)cub->p->ray[ray]->map.y, tmp_side, cub->p->ray[ray]->side);*/
		// 	cub->p->nb_wall++;
		// 	old_map_x = cub->p->ray[ray]->map.x;
		// 	old_map_y = cub->p->ray[ray]->map.y;
		// 	tmp_side = cub->p->ray[ray]->side;
		// }

		// if (tmp_side != cub->p->ray[ray]->side)
		// {
		// 	printf("tmp_side = %d and new_side = %d\n", tmp_side, cub->p->ray[ray]->side);
		// 	cub->p->nb_wall++;
		// 	tmp_side = cub->p->ray[ray]->side;
		// }

		// if ((int)cub->p->ray[ray]->map.x != old_map_x || (int)cub->p->ray[ray]->map.y != old_map_y || ray == WIN_WIDTH - 1 || ray == 0)
		// {
		// 	old_map_x = cub->p->ray[ray]->map.x;
		// 	old_map_y = cub->p->ray[ray]->map.y;
		// 	if (ray != 0 && ray != WIN_WIDTH - 1)
		// 		cub->p->nb_wall++;
		// }
	}
	// printf("ray[%d] = %d\tray [%d] = %d\tray [%d] = %d\n", 300, cub->p->ray[300]->side, 700, cub->p->ray[700]->side, 1000, cub->p->ray[1000]->side);
	// printf("nb_wall = %d\n\n", cub->p->nb_wall);
}

int	calcul_wall_bloc(t_cub *cub)
{
	(void) cub;
	// int	ray;
	// int	tmpWidth = 0;
	// int old_map_x;
	// int old_map_y;
	// int	tmpIndex;

	// int tmp_side;
	
	// (void)ray;
	// (void)tmpWidth;
	// (void)tmpIndex;

	// if (cub->p->wall)
	// 	free(cub->p->wall);
	// cub->p->wall = ft_calloc(cub->p->nb_wall + 1, sizeof(t_wall));
	// if (!cub->p->wall)
	// 	return (display_error("cub->p->wall", 4));
	// ray = -1;
	// int index_wall = 0;
	
	// old_map_x = cub->p->ray[0]->wall.x / GRID_MINI;
	// old_map_y = cub->p->ray[0]->wall.y / GRID_MINI;
	// tmp_side = cub->p->ray[0]->side;
	// (void)index_wall;
	// (void)tmp_side;
	// (void)old_map_x;
	// (void)old_map_y;
	// while (cub->p->ray[++ray])
	// {
	// 	// // if (((int)cub->p->ray[ray]->map.x != old_map_x || (int)cub->p->ray[ray]->map.y != old_map_y || ray == 0 || ray == WIN_WIDTH - 1))
	// 	// if ((old_map_x != (int)cub->p->ray[ray]->map.x || old_map_y != (int)cub->p->ray[ray]->map.y) || tmp_side != cub->p->ray[ray]->side || ray == WIN_WIDTH - 1)
	// 	// {
	// 	// 	// use map x or y depending of side wall
	// 	// 	// int middle_wall = get_middle(cub, index_wall);
			
	// 	// 	if (ray != 0)
	// 	// 	{
	// 	// 		cub->p->wall[index_wall].width = tmpWidth;
	// 	// 		// middle_wall = get_middle(cub, index_wall);
	// 	// 		if (cub->p->ray[ray]->side == NORTH)
	// 	// 		{
	// 	// 			cub->p->wall[index_wall].percent_end = 100 - (cub->p->ray[ray - 1]->map.x - (int)cub->p->ray[ray - 1]->map.x) * 100;
	// 	// 			cub->p->wall[index_wall].side = 1;
	// 	// 			// printf("%d/   NORTH: %d\n", ray, cub->p->ray[ray]->side);
	// 	// 		}
	// 	// 		else if (cub->p->ray[ray]->side == SOUTH)
	// 	// 		{
	// 	// 			cub->p->wall[index_wall].percent_end = (cub->p->ray[ray - 1]->map.x - (int)cub->p->ray[ray - 1]->map.x) * 100;
	// 	// 			cub->p->wall[index_wall].side = 2;
	// 	// 			// printf("%d/   SOUTH: %d\n", ray, cub->p->ray[ray]->side);
	// 	// 		}
	// 	// 		else if (cub->p->ray[ray]->side == EAST)
	// 	// 		{
	// 	// 			cub->p->wall[index_wall].percent_end = (cub->p->ray[ray - 1]->map.y - (int)cub->p->ray[ray - 1]->map.y) * 100;
	// 	// 			cub->p->wall[index_wall].side = 3;
	// 	// 			// printf("%d/   EAST: %d\n", ray, cub->p->ray[ray]->side);
	// 	// 		}
	// 	// 		else if (cub->p->ray[ray]->side == WEST)
	// 	// 		{
	// 	// 			cub->p->wall[index_wall].percent_end = (cub->p->ray[ray - 1]->map.y - (int)cub->p->ray[ray - 1]->map.y) * 100;
	// 	// 			cub->p->wall[index_wall].side = 4;
	// 	// 			// printf("%d/   WEST: %d\n", ray, cub->p->ray[ray]->side);
	// 	// 		}
	// 	// 	}
	// 	// 	if (ray == WIN_WIDTH - 1)
	// 	// 		break;
	// 	// 	tmpWidth = 0;
	// 	// 	index_wall++;
	// 	// 	if (cub->p->ray[ray]->side == NORTH)
	// 	// 		cub->p->wall[index_wall].percent_start = 100 - (cub->p->ray[ray]->map.x - (int)cub->p->ray[ray]->map.x) * 100;
	// 	// 	if (cub->p->ray[ray]->side == SOUTH)
	// 	// 		cub->p->wall[index_wall].percent_start = (cub->p->ray[ray]->map.x - (int)cub->p->ray[ray]->map.x) * 100;
	// 	// 	else if (cub->p->ray[ray]->side == EAST)
	// 	// 		cub->p->wall[index_wall].percent_start = ((cub->p->ray[ray]->map.y - (int)cub->p->ray[ray]->map.y) * 100);
	// 	// 	else if (cub->p->ray[ray]->side == WEST)
	// 	// 		cub->p->wall[index_wall].percent_start = (cub->p->ray[ray]->map.y - (int)cub->p->ray[ray]->map.y) * 100;
	// 	// 	old_map_x = cub->p->ray[ray]->map.x;
	// 	// 	old_map_y = cub->p->ray[ray]->map.y;
	// 	// }
	// 	// tmpWidth++;

	// 	if (ray == 0)
	// 	{
	// 		if (cub->p->ray[ray]->side == NORTH)
	// 			cub->p->wall[index_wall].percent_start = 100 - (cub->p->ray[ray]->map.x - (int)cub->p->ray[ray]->map.x) * 100;
	// 		else if (cub->p->ray[ray]->side == SOUTH)
	// 			cub->p->wall[index_wall].percent_start = (cub->p->ray[ray]->map.x - (int)cub->p->ray[ray]->map.x) * 100;
	// 		else if (cub->p->ray[ray]->side == EAST)
	// 			cub->p->wall[index_wall].percent_start = ((cub->p->ray[ray]->map.y - (int)cub->p->ray[ray]->map.y) * 100);
	// 		else if (cub->p->ray[ray]->side == WEST)
	// 			cub->p->wall[index_wall].percent_start = (cub->p->ray[ray]->map.y - (int)cub->p->ray[ray]->map.y) * 100;
	// 	}

	// 	if ((old_map_x != (int)cub->p->ray[ray]->map.x || old_map_y != (int)cub->p->ray[ray]->map.y) || tmp_side != cub->p->ray[ray]->side || ray == WIN_WIDTH - 1)
	// 	{
	// 		// printf("NEW WALL %d\t%dpx\toldX = %d\tnewX = %d\toldY = %d\tnewY = %d\toldSide = %d\tnewSide = %d\n", index_wall, 
	// 		// ray, old_map_x, (int)cub->p->ray[ray]->map.x, old_map_y, (int)cub->p->ray[ray]->map.y, tmp_side, cub->p->ray[ray]->side);

	// 		cub->p->wall[index_wall].width = tmpWidth;

	// 		if (cub->p->ray[ray - 1]->side == NORTH)
	// 		// {
	// 			cub->p->wall[index_wall].percent_end = 100 - (cub->p->ray[ray - 1]->map.x - (int)cub->p->ray[ray - 1]->map.x) * 100;
	// 			// cub->p->wall[index_wall].side = 2;
	// 			// printf("%d/   NORTH: %d\n", ray, cub->p->ray[ray - 1]->side);
	// 		// }
	// 		else if (cub->p->ray[ray - 1]->side == SOUTH)
	// 		// {
	// 			cub->p->wall[index_wall].percent_end = (cub->p->ray[ray - 1]->map.x - (int)cub->p->ray[ray - 1]->map.x) * 100;
	// 			// cub->p->wall[index_wall].side = 3;
	// 			// printf("%d/   SOUTH: %d\n", ray, cub->p->ray[ray - 1]->side);
	// 		// }
	// 		else if (cub->p->ray[ray - 1]->side == EAST)
	// 		// {
	// 			cub->p->wall[index_wall].percent_end = (cub->p->ray[ray - 1]->map.y - (int)cub->p->ray[ray - 1]->map.y) * 100;
	// 			// cub->p->wall[index_wall].side = 1;
	// 			// printf("%d/   EAST: %d\n", ray, cub->p->ray[ray - 1]->side);
	// 		// }
	// 		else if (cub->p->ray[ray - 1]->side == WEST)
	// 		// {
	// 			cub->p->wall[index_wall].percent_end = (cub->p->ray[ray - 1]->map.y - (int)cub->p->ray[ray - 1]->map.y) * 100;
	// 			// cub->p->wall[index_wall].side = 0;
	// 			// printf("%d/   WEST: %d\n", ray, cub->p->ray[ray - 1]->side);
	// 		// }

	// 		tmpWidth = 0;
	// 		index_wall++;
	// 		if (cub->p->ray[ray]->side == NORTH)
	// 			cub->p->wall[index_wall].percent_start = 100 - (cub->p->ray[ray]->map.x - (int)cub->p->ray[ray]->map.x) * 100;
	// 		else if (cub->p->ray[ray]->side == SOUTH)
	// 			cub->p->wall[index_wall].percent_start = (cub->p->ray[ray]->map.x - (int)cub->p->ray[ray]->map.x) * 100;
	// 		else if (cub->p->ray[ray]->side == EAST)
	// 			cub->p->wall[index_wall].percent_start = ((cub->p->ray[ray]->map.y - (int)cub->p->ray[ray]->map.y) * 100);
	// 		else if (cub->p->ray[ray]->side == WEST)
	// 			cub->p->wall[index_wall].percent_start = (cub->p->ray[ray]->map.y - (int)cub->p->ray[ray]->map.y) * 100;

	// 		old_map_x = cub->p->ray[ray]->map.x;
	// 		old_map_y = cub->p->ray[ray]->map.y;
	// 		tmp_side = cub->p->ray[ray]->side;
	// 	}
	// 	tmpWidth++;
	// }
	// printf("end\n");
	return (0);
}

void	generate_3d(t_cub *cub)
{
	int	x;
	// int tmp_index;
	// int tmp_wall;
	// int old_map_x;
	// int old_map_y;
	// int tmp_side;
	
	// (void)tmp_wall;
	// (void)tmp_index;
	(void)draw_wall;
	
	if (cub->imgs->back.img)
		mlx_destroy_image(cub->mlx, cub->imgs->back.img);
	cub->imgs->back.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->imgs->back.addr = mlx_get_data_addr(cub->imgs->back.img, &cub->imgs->back.bits_per_pixel, &cub->imgs->back.line_length, &cub->imgs->back.endian);
	x = -1;
	put_floor_and_ceiling(cub);

	calcul_ray(cub);
	if (calcul_wall_bloc(cub) != 0)
		printf("return malloc crash\n");

	// tmp_index = 0;
	// tmp_wall = 0;
	// old_map_x = cub->p->ray[0]->wall.x / GRID_MINI;
	// old_map_y = cub->p->ray[0]->wall.y / GRID_MINI;
	// tmp_side = cub->p->ray[0]->side;
	while (cub->p->ray[++x])
	{
		// double	show_width = cub->p->wall[cub->p->ray[x]->index_wall].width;
		// double	full_width = cub->p->wall[cub->p->ray[x]->index_wall].width * 100 / (cub->p->wall[cub->p->ray[x]->index_wall].percent_end - cub->p->wall[cub->p->ray[x]->index_wall].percent_start);
		// double	percent_show = show_width / full_width * 100;
		// double	percent_line = 128 / full_width;
		// (void)percent_show;
		// (void)percent_line;

		// if ((old_map_x != (int)cub->p->ray[x]->map.x || old_map_y != (int)cub->p->ray[x]->map.y) || tmp_side != cub->p->ray[x]->side)
		// {
		// 	tmp_wall++;
		// 	tmp_index = 0;
		// 	old_map_x = cub->p->ray[x]->map.x;
		// 	old_map_y = cub->p->ray[x]->map.y;
		// 	tmp_side = cub->p->ray[x]->side;
		// }

		// int	px_column;
		// if (cub->p->ray[x]->side == EAST)
		// 	px_column = 128 - ((128 * ((cub->p->wall[cub->p->ray[x]->index_wall].percent_start) / 100)) + (tmp_index * percent_line));
		// else
		// 	px_column = (128 * ((cub->p->wall[cub->p->ray[x]->index_wall].percent_start) / 100)) + (tmp_index * percent_line);
		// int	px_column = 128;


		// if (px_column <= 0)
		// 	px_column = 1;
		// else if (px_column == 127)
		// 	px_column++;

		// if (x == 639)
		// 	printf("px_column: %d\n", px_column);

		if (cub->p->ray[x]->margin > 0 && cub->p->ray[x]->margin < WIN_HEIGHT)
			draw_wall(cub, x, cub->p->ray[x]->margin, cub->p->ray[x]->margin + cub->p->ray[x]->wall_height - 1, cub->p->ray[x]);  // temporary
		else
			draw_wall(cub, x, 0, WIN_HEIGHT, cub->p->ray[x]);  // temporary
		// tmp_index++;
		// // printf("wall %d/   side: %d   width: %d   percent_start: %f   percent_end: %f\n", x, cub->p->ray[x]->side, cub->p->wall[x].width, cub->p->wall[x].percent_start, cub->p->wall[x].percent_end);
	}
	// for (int i = 0; i < cub->p->nb_wall; i++)
	// {
	// 	printf("wall %d/   side: %d   width: %d   percent_start: %f   percent_end: %f\n", i, cub->p->wall[i].side, cub->p->wall[i].width, cub->p->wall[i].percent_start, cub->p->wall[i].percent_end);
	// }
	// printf("\n");
}
