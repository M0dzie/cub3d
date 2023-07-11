/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:11:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/10 19:44:42 by mehdisapin       ###   ########.fr       */
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

int	check_keycode(int key, t_cub *cub)
{
	if (key == W)
		move_player(cub, cub->p->dir, 1);
	if (key == S)
		move_player(cub, cub->p->dir, -1);
	if (key == D)
		move_player(cub, cub->p->dir_ew, -1);
	if (key == A)
		move_player(cub, cub->p->dir_ew, 1);
	if (key == R_ARROW)
		rotate_player(cub, 1);
	if (key == L_ARROW)
		rotate_player(cub, -1);
	if (key == ESC)
		exit(0);
	return (0);
}

int	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->imgs = malloc(sizeof(t_imgs));
	if (!cub->imgs)
		return (-1);
	if (parse_xpm(cub) != 0)
		return (exit_cub(cub), -1);
	init_image(cub);
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	mlx_hook(cub->win, 2, 1l << 0, check_keycode, cub);
	mlx_hook(cub->win, 17, 1l << 0, exit_cub, cub);
	mlx_loop_hook(cub->mlx, &render_cub3d, cub);
	mlx_loop(cub->mlx);
	return (0);
}
