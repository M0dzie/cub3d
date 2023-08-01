/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:11:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/08/01 09:39:39 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

static int	actions(t_cub *cub)
{
	generate_3d(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img_cub.img, 0, 0);
	mlx_destroy_image(cub->mlx, cub->img_cub.img);
	if (cub->key.w)
		move_player(cub, cub->p->pos.coef_ns, 1);
	if (cub->key.s)
		move_player(cub, cub->p->pos.coef_ns, -1);
	if (cub->key.a)
		move_player(cub, cub->p->pos.coef_we, 1);
	if (cub->key.d)
		move_player(cub, cub->p->pos.coef_we, -1);
	if (cub->key.l_arrow)
	{
		cub->p->pos.angle = get_angle(cub->p->pos.angle, -ROTATE);
		move_player(cub, cub->p->pos.coef_ns, 0);
	}
	if (cub->key.r_arrow)
	{
		cub->p->pos.angle = get_angle(cub->p->pos.angle, ROTATE);
		move_player(cub, cub->p->pos.coef_ns, 0);
	}
	return (0);
}

static void	init_keys(t_cub *cub)
{
	cub->key.w = FALSE;
	cub->key.s = FALSE;
	cub->key.a = FALSE;
	cub->key.d = FALSE;
	cub->key.l_arrow = FALSE;
	cub->key.r_arrow = FALSE;
}

int	init_mlx(t_cub *cub)
{
	cub->img_cub.img = NULL;
	cub->win = NULL;
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (display_error("cub3d", 14), exit_cub(cub, 1));
	if (parse_xpm(cub) != 0)
		return (exit_cub(cub, 1));
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	calcul_coef(cub);
	init_keys(cub);
	mlx_hook(cub->win, 2, 1l << 0, &init_key_press, cub);
	mlx_hook(cub->win, 3, 1l << 1, &init_key_release, cub);
	mlx_hook(cub->win, 17, 1l << 0, exit_cub, cub);
	mlx_loop_hook(cub->mlx, &actions, cub);
	mlx_loop(cub->mlx);
	return (0);
}
