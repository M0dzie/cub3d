/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:11:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/20 21:17:33 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/cub3d.h"

// static void	init_image(t_cub *cub)
// {
// 	cub->game.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
// 	cub->game.addr = mlx_get_data_addr(cub->game.img, \
// 	&cub->game.bits_per_pixel, &cub->game.line_length, \
// 	&cub->game.endian);
// }

// static int	init_key_press(int key, t_cub *cub)
// {
// 	if (key == ESC)
// 		exit_cub(cub, 1);
// 	if (key == W)
// 		cub->key.w = TRUE;
// 	if (key == S)
// 		cub->key.s = TRUE;
// 	if (key == A)
// 		cub->key.a = TRUE;
// 	if (key == D)
// 		cub->key.d = TRUE;
// 	if (key == L_ARROW)
// 		cub->key.l_arrow = TRUE;
// 	if (key == R_ARROW)
// 		cub->key.r_arrow = TRUE;
// 	return (0);
// }

// static int	init_key_release(int key, t_cub *cub)
// {
// 	if (key == W)
// 		cub->key.w = FALSE;
// 	if (key == S)
// 		cub->key.s = FALSE;
// 	if (key == A)
// 		cub->key.a = FALSE;
// 	if (key == D)
// 		cub->key.d = FALSE;
// 	if (key == L_ARROW)
// 		cub->key.l_arrow = FALSE;
// 	if (key == R_ARROW)
// 		cub->key.r_arrow = FALSE;
// 	return (0);
// }

// int	init_mlx(t_cub *cub)
// {
// 	cub->game.img = NULL;
// 	cub->win = NULL;
// 	cub->mlx = mlx_init();
// 	if (!cub->mlx)
// 		return (display_error("cub3d", 14), exit_cub(cub, 1), -1);
// 	if (parse_xpm(cub) != 0)
// 		return (exit_cub(cub, 1), -1);
// 	init_image(cub);
// 	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
// 	mlx_hook(cub->win, 2, 1l << 0, &init_key_press, cub);
// 	mlx_hook(cub->win, 3, 1l << 1, &init_key_release, cub);
// 	mlx_hook(cub->win, 17, 1l << 0, exit_cub, cub);
// 	mlx_loop_hook(cub->mlx, &render_cub3d, cub);
// 	mlx_loop(cub->mlx);
// 	return (0);
// }

#include "../../includes/cub3d.h"

static int	ft_exit(void)
{
	exit(0);
	return (1);
}

double	get_angle(double angle, int rotation)
{
	angle += rotation;
	if (angle > 359)
		angle -= 360;
	else if (angle < 0)
		angle += 360;
	return (angle);
}

void	set_angle(t_cub *cub, int sign)
{
	cub->p->pos.angle = get_angle(cub->p->pos.angle, SPEED_ANGLE * sign);
}

static int	init_key_press(int key, t_cub *cub)
{
	if (key == ESC)
		ft_exit();
		// exit_cub(cub, 1);
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
	if (key == M)
	{
		if (cub->imgs->show_mini)
		{
			mlx_put_image_to_window(cub->mlx, cub->win, cub->imgs->back.img, 0, 0);
			cub->imgs->show_mini = 0;
		}
		else
		{
			cub->imgs->show_mini = 1;
			render_minimap(cub);
		}
	}
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
		set_angle(cub, -1);
		move_player(cub, cub->p->pos.coef_ns, 0);
	}
	if (cub->key.r_arrow)
	{
		set_angle(cub, 1);
		move_player(cub, cub->p->pos.coef_ns, 0);
	}
	return (0);
}

void	display_images(t_cub *cub)
{
	mlx_put_image_to_window(cub->mlx, cub->win, cub->imgs->back.img, 0, 0);
	if (cub->imgs->show_mini)
	{
		mlx_put_image_to_window(cub->mlx, cub->win, cub->imgs->minimap.img, \
		(WIN_WIDTH / 2) - (cub->map->width * GRID_MINI / 2), (WIN_HEIGHT / 2) - \
		(cub->map->height * GRID_MINI / 2));
	}
}

int	init_mlx(t_cub *cub)
{
	cub->win = NULL;
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (display_error("cub3d", 14), ft_exit(), -1);
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	cub->imgs = malloc(sizeof(t_imgs));
	cub->imgs->show_mini = 1;

	generate_minimap(cub);
	calcul_coef(cub);
	generate_player(cub);
	generate_3d(cub);

	display_images(cub);

	mlx_hook(cub->win, 2, 1l << 0, &init_key_press, cub);
	mlx_hook(cub->win, 3, 1l << 1, &init_key_release, cub);
	// mlx_hook(cub->win, 17, 1l << 0, exit_cub, cub);
	mlx_hook(cub->win, 17, 1l << 0, ft_exit, cub);
	mlx_loop_hook(cub->mlx, &actions, cub);
	mlx_loop(cub->mlx);
	return (0);
}
