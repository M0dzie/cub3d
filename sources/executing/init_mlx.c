/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:11:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/19 18:45:00 by thmeyer          ###   ########.fr       */
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

static int	init_key_press(int key, t_cub *cub)
{
	if (key == ESC)
		exit_cub(cub, 1);
	if (key == W)
		cub->key.w = TRUE;
	if (key == S)
		cub->key.s = TRUE;
	if (key == A)
		cub->key.a = TRUE;
	if (key == D)
		cub->key.d = TRUE;
	if (key == L_ARROW)
		cub->key.l_arrow = TRUE;
	if (key == R_ARROW)
		cub->key.r_arrow = TRUE;
	return (0);
}

static int	init_key_release(int key, t_cub *cub)
{
	if (key == W)
		cub->key.w = FALSE;
	if (key == S)
		cub->key.s = FALSE;
	if (key == A)
		cub->key.a = FALSE;
	if (key == D)
		cub->key.d = FALSE;
	if (key == L_ARROW)
		cub->key.l_arrow = FALSE;
	if (key == R_ARROW)
		cub->key.r_arrow = FALSE;
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
	mlx_hook(cub->win, 2, 1l << 0, &init_key_press, cub);
	mlx_hook(cub->win, 3, 1l << 1, &init_key_release, cub);
	mlx_hook(cub->win, 17, 1l << 0, exit_cub, cub);
	mlx_loop_hook(cub->mlx, &render_cub3d, cub);
	mlx_loop(cub->mlx);
	return (0);
}
