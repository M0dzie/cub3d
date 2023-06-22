/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:11:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/22 15:40:39 by msapin           ###   ########.fr       */
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
		move_player(cub, cub->p->pos.coef_ns, 0);
	}
	if (keycode == R_ARROW)
	{
		cub->p->pos.angle = get_angle(cub->p->pos.angle, SPEED_ANGLE);
		move_player(cub, cub->p->pos.coef_ns, 0);
	}
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

int	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	cub->imgs = malloc(sizeof(t_imgs));
	if (!cub->imgs)
		return (-1);
	cub->imgs->minimap.img = NULL;
	cub->imgs->back.img = NULL;
	if (parse_xpm(cub) != 0)
		return (-1);
	render_cub3d(cub);
	mlx_hook(cub->win, 2, 1l << 0, check_keycode, cub);
	mlx_hook(cub->win, 17, 1l << 0, exit_cub, cub);
	mlx_loop_hook(cub->mlx, render_cub3d, cub);
	mlx_loop(cub->mlx);
	return (0);
}
