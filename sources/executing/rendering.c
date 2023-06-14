/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:43:13 by msapin            #+#    #+#             */
/*   Updated: 2023/06/14 14:07:04 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

int	is_wall(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	if (*(unsigned int *)dst == 0x00202020)
		return (1);
	return (0);
}

double	distance_to_wall(t_cub *cub, t_vector coef, int sign, int ray)
{
	t_vector	tmp;
	double		distance;

	tmp.x = cub->p->pos.start.x;
	tmp.y = cub->p->pos.start.y + (double)GRID_MINI / 2;
	distance = 0;
	while (1)
	{
		if (tmp.x > 0 && tmp.y > 0)
		{
			if (is_wall(&cub->imgs->minimap, tmp.x + GRID_MINI / 2, tmp.y - 1))
				break ;
		}
		else
			break ;
		tmp.x += (coef.x) * sign;
		tmp.y += (coef.y) * sign;
		// tmp.x += (1 / GRID_MINI) * (coef.x) * sign;
		// tmp.y += (1 / GRID_MINI) * (coef.y) * sign;
		distance++;
	}
	if (!ray)
		distance -= GRID_MINI / 3;
	return (distance);
}

void	calcul_distance(t_cub *cub)
{
	cub->p->pos.dist.n = distance_to_wall(cub, cub->p->pos.coef_ns, 1, 0);
	cub->p->pos.dist.s = distance_to_wall(cub, cub->p->pos.coef_ns, -1, 0);
	cub->p->pos.dist.e = distance_to_wall(cub, cub->p->pos.coef_we, 1, 0);
	cub->p->pos.dist.w = distance_to_wall(cub, cub->p->pos.coef_we, -1, 0);
	cub->p->pos.dist.nw = distance_to_wall(cub, cub->p->pos.coef_nwse, 1, 0);
	cub->p->pos.dist.se = distance_to_wall(cub, cub->p->pos.coef_nwse, -1, 0);
	cub->p->pos.dist.ne = distance_to_wall(cub, cub->p->pos.coef_nesw, 1, 0);
	cub->p->pos.dist.sw = distance_to_wall(cub, cub->p->pos.coef_nesw, -1, 0);
}

void	render_minimap(t_cub *cub)
{
	generate_minimap(cub);
	calcul_coef(cub);
	generate_player(cub);
	generate_3d(cub);
	display_images(cub);
}

void	move_player(t_cub *cub, t_vector coef, int sign)
{
	t_vector	tmp_coef;

	calcul_coef(cub);
	tmp_coef.x = (coef.x * SPEED_MINI) * sign;
	tmp_coef.y = (coef.y * SPEED_MINI) * sign;
	if (sign)
	{
		cub->p->pos.start.x += tmp_coef.x;
		cub->p->pos.start.y += tmp_coef.y;
		calcul_distance(cub);
		if (cub->p->pos.dist.n < 0 || cub->p->pos.dist.s < 0 \
		|| cub->p->pos.dist.w < 0 || cub->p->pos.dist.e < 0 \
		|| cub->p->pos.dist.nw < 0 || cub->p->pos.dist.se < 0 \
		|| cub->p->pos.dist.ne < 0 || cub->p->pos.dist.sw < 0)
		{
			cub->p->pos.start.x -= tmp_coef.x;
			cub->p->pos.start.y -= tmp_coef.y;
		}
	}
	render_minimap(cub);
}

int	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	if (*(unsigned int *)dst == 0x00202020)
		return (0);
	*(unsigned int *)dst = color;
	return (1);
}

void	put_miniwall(t_data data, int start_x, int start_y)
{
	int	y;
	int	x;

	y = -1;
	while (++y < GRID_MINI)
	{
		x = -1;
		while (++x < GRID_MINI)
			put_pixel(&data, x + start_x, y + start_y, 0x00202020);
	}
}

void	put_minifloor(t_data data, int start_x, int start_y)
{
	int	y;
	int	x;

	y = -1;
	while (++y < GRID_MINI)
	{
		x = -1;
		while (++x < GRID_MINI)
		{
			if (y == (GRID_MINI - 1) || x == (GRID_MINI - 1) || y == 0 || x == 0)
				put_pixel(&data, x + start_x, y + start_y, 0x00C6C6C6);
			else
				put_pixel(&data, x + start_x, y + start_y, 0x00CDCDCD);
		}
	}
}

void	generate_minimap(t_cub *cub)
{
	int		y;
	int		x;
	char	c;

	if (cub->imgs->minimap.img)
		mlx_destroy_image(cub->mlx, cub->imgs->minimap.img);
	cub->imgs->minimap.img = mlx_new_image(cub->mlx, cub->map->width * GRID_MINI, cub->map->height * GRID_MINI);
	cub->imgs->minimap.addr = mlx_get_data_addr(cub->imgs->minimap.img, &cub->imgs->minimap.bits_per_pixel, &cub->imgs->minimap.line_length, &cub->imgs->minimap.endian);
	y = -1;
	while (++y < (cub->map->height))
	{
		x = -1;
		while (++x < (cub->map->width))
		{
			c = cub->map->array[y][x];
			if (c == '1')
				put_miniwall(cub->imgs->minimap, x * GRID_MINI, y * GRID_MINI);
			else if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
				put_minifloor(cub->imgs->minimap, x * GRID_MINI, y * GRID_MINI);
		}
	}
}

void	draw_player_body(t_cub *cub)
{
	int			angle;
	int			i;
	t_vector	start;
	t_vector	coef;

	angle = -1;
	while (++angle < 360)
	{
		start.x = cub->p->pos.start.x;
		start.y = cub->p->pos.start.y;
		coef.x = sin(angle * M_PI / 180);
		coef.y = -cos(angle * M_PI / 180);
		i = -1;
		while (++i < GRID_MINI / 3)
		{
			if (start.x > 0 && start.y > 0)
				put_pixel(&cub->imgs->minimap, start.x + GRID_MINI / 2, start.y + GRID_MINI / 2, 0x0082180e);
			else
				break ;
			start.x += coef.x;
			start.y += coef.y;
		}
	}
}

void	draw_until_wall(t_cub *cub, t_ray *ray, t_vector coef, int sign)
{
	t_vector	tmp;

	tmp.x = ray->start.x;
	tmp.y = ray->start.y + (double)GRID_MINI / 2;
	while (1)
	{
		if (tmp.x > 0 && tmp.y > 0)
		{
			if (!put_pixel(&cub->imgs->minimap, tmp.x + GRID_MINI / 2, tmp.y - 1, 0x00ff1500))
				break ;
		}
		else
			break ;
		tmp.x += (coef.x) * sign;
		tmp.y += (coef.y) * sign;
	}
}

void	draw_ray(t_cub *cub, t_vector coef, int sign)
{
	t_vector	tmp;

	tmp.x = cub->p->pos.start.x;
	tmp.y = cub->p->pos.start.y + (double)GRID_MINI / 2;
	while (1)
	{
		if (tmp.x > 0 && tmp.y > 0)
		{
			if (!put_pixel(&cub->imgs->minimap, tmp.x + GRID_MINI / 2, tmp.y - 1, 0x00ff1500))
			{
				// cub->p->ray[i]->wall.x = tmp.x;
				// cub->p->ray[i]->wall.y = tmp.y;
				break ;
			}
		}
		else
			break ;
		tmp.x += (coef.x) * sign;
		tmp.y += (coef.y) * sign;
	}
}

void	draw_fov(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < WIN_WIDTH)
		draw_ray(cub, cub->p->ray[i]->coef_ns, 1);
}

void	generate_player(t_cub *cub)
{
	draw_player_body(cub);
	draw_fov(cub);
}
