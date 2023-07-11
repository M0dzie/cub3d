/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:11:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/11 12:04:18 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_image(t_cub *cub)
{
	cub->imgs->game.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->imgs->game.addr = mlx_get_data_addr(cub->imgs->game.img, \
	&cub->imgs->game.bits_per_pixel, &cub->imgs->game.line_length, \
	&cub->imgs->game.endian);
}

static int	check_keycode(int key, t_cub *cub)
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
		exit_cub(cub);
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
