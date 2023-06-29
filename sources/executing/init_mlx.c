/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:11:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/29 15:08:04 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
// #include "../../includes/thomas.h"

double	get_angle(double angle, int rotation)
{
	angle += rotation;
	if (angle > 359)
		angle -= 360;
	else if (angle < 0)
		angle += 360;
	return (angle);
}

static int	check_keycode(int keycode, t_cub *cub)
{
	if (keycode == ESC)
		exit_cub(cub);
	if (keycode == W)
		move_player(cub, cub->p->pos.coef_ns, 1);
	if (keycode == S)
		move_player(cub, cub->p->pos.coef_ns, -1);
	if (keycode == A)
		move_player(cub, cub->p->pos.coef_we, 1);
	if (keycode == D)
		move_player(cub, cub->p->pos.coef_we, -1);
	if (keycode == L_ARROW)
	{
		cub->p->pos.angle = get_angle(cub->p->pos.angle, -SPEED_ANGLE);

		double rotSpeed = 0.1;
		double oldDirX = cub->p->dir.x;
		cub->p->dir.x = cub->p->dir.x * cos(rotSpeed) - cub->p->dir.y * sin(rotSpeed);
		cub->p->dir.y = oldDirX * sin(rotSpeed) + cub->p->dir.y * cos(rotSpeed);
		double oldPlaneX = cub->p->fov.x;
		cub->p->fov.x = cub->p->fov.x * cos(rotSpeed) - cub->p->fov.y * sin(rotSpeed);
		cub->p->fov.y = oldPlaneX * sin(rotSpeed) + cub->p->fov.y * cos(rotSpeed);

		move_player(cub, cub->p->pos.coef_ns, 0);
	}
	if (keycode == R_ARROW)
	{
		cub->p->pos.angle = get_angle(cub->p->pos.angle, SPEED_ANGLE);

		double rotSpeed = 0.1;
		double oldDirX = cub->p->dir.x;
		cub->p->dir.x = cub->p->dir.x * cos(-rotSpeed) - cub->p->dir.y * sin(-rotSpeed);
		cub->p->dir.y = oldDirX * sin(-rotSpeed) + cub->p->dir.y * cos(-rotSpeed);
		double oldPlaneX = cub->p->fov.x;
		cub->p->fov.x = cub->p->fov.x * cos(-rotSpeed) - cub->p->fov.y * sin(-rotSpeed);
		cub->p->fov.y = oldPlaneX * sin(-rotSpeed) + cub->p->fov.y * cos(-rotSpeed);

		move_player(cub, cub->p->pos.coef_ns, 0);
	}
	// printf("dirX %f  dirY %f  ", cub->p->dir.x, cub->p->dir.y);
	// printf("planeX %f  planeY %f\n", cub->p->fov.x, cub->p->fov.y);
	// if (keycode == M)
	// {
	// 	if (cub->imgs->show_mini)
	// 	{
	// 		mlx_put_image_to_window(cub->mlx, cub->win, cub->imgs->back.img, 0, 0);
	// 		cub->imgs->show_mini = 0;
	// 	}
	// 	else
	// 	{
	// 		cub->imgs->show_mini = 1;
	// 		render_cub3d(cub);
	// 	}
	// }
	return (1);
}

void	init_image(t_cub *cub)
{
	cub->imgs->game.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->imgs->game.addr = mlx_get_data_addr(cub->imgs->game.img, \
	&cub->imgs->game.bits_per_pixel, &cub->imgs->game.line_length, \
	&cub->imgs->game.endian);
	cub->imgs->minimap.img = mlx_new_image(cub->mlx, cub->map->width * \
	GRID_MINI, cub->map->height * GRID_MINI);
	cub->imgs->minimap.addr = mlx_get_data_addr(cub->imgs->minimap.img, \
	&cub->imgs->minimap.bits_per_pixel, &cub->imgs->minimap.line_length, \
	&cub->imgs->minimap.endian);
}

int	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	cub->imgs = malloc(sizeof(t_imgs));
	if (!cub->imgs)
		return (-1);
	if (parse_xpm(cub) != 0)
		return (exit_cub(cub), -1);
	init_image(cub);
	mlx_hook(cub->win, 2, 1L << 0, check_keycode, cub);
	mlx_hook(cub->win, 17, 1L << 0, exit_cub, cub);
	mlx_loop_hook(cub->mlx, render_cub3d, cub);
	mlx_loop(cub->mlx);
	return (0);
}
