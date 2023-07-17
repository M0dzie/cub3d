/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:11:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/17 17:35:48 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_image(t_cub *cub)
{
	cub->game.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->game.addr = mlx_get_data_addr(cub->game.img, \
	&cub->game.bits_per_pixel, &cub->game.line_length, \
	&cub->game.endian);
}

static int	check_keycode(int key, t_cub *cub)
{
	if (key == W)
		move_player(cub, cub->p->axis, 1);
	if (key == S)
		move_player(cub, cub->p->axis, -1);
	if (key == D)
		move_player(cub, cub->p->axis_side, -1);
	if (key == A)
		move_player(cub, cub->p->axis_side, 1);
	if (key == R_ARROW)
		rotate_player(cub, 1);
	if (key == L_ARROW)
		rotate_player(cub, -1);
	if (key == ESC)
		exit_cub(cub, 1);
	return (0);
}

int	init_mlx(t_cub *cub)
{
	cub->game.img = NULL;
	cub->win = NULL;
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (display_error("cub3d", 14), exit_cub(cub, 1), -1);
	if (parse_xpm(cub) != 0)
		return (exit_cub(cub, 1), -1);
	init_image(cub);
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	mlx_hook(cub->win, 2, 1l << 0, check_keycode, cub);
	mlx_hook(cub->win, 17, 1l << 0, exit_cub, cub);
	mlx_loop_hook(cub->mlx, &render_cub3d, cub);
	mlx_loop(cub->mlx);
	return (0);
}
