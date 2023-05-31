/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:11:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/31 23:44:00 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
// #include "../../includes/thomas.h"

static int	ft_exit(void)
{
	exit(0);
	return (1);
}

void	new_angle(t_cub *cub, int sign)
{
	cub->p->angle += (SPEED_ANGLE * sign);
	if (cub->p->angle > 359)
		cub->p->angle -= 360;
	else if (cub->p->angle < 0)
		cub->p->angle += 360;
	cub->p->coef_ns.x = sin(cub->p->angle * M_PI / 180);
	cub->p->coef_ns.y = -cos(cub->p->angle * M_PI / 180);
	cub->p->coef_we.x = sin((cub->p->angle - 90) * M_PI / 180);
	cub->p->coef_we.y = -cos((cub->p->angle - 90) * M_PI / 180);
}

static int	check_keycode(int keycode, t_cub *cub)
{
	// init_data_raycaster(cub);
	// get_next_wall(cub);
	if (keycode == ESC)
		ft_exit();
	if (keycode == W)
	{
		cub->p->mini_x += cub->p->coef_ns.x * SPEED_MINI;
		cub->p->mini_y += cub->p->coef_ns.y * SPEED_MINI;
		move_player(cub);
	}
	if (keycode == S)
	{
		cub->p->mini_x -= cub->p->coef_ns.x * SPEED_MINI;
		cub->p->mini_y -= cub->p->coef_ns.y * SPEED_MINI;
		move_player(cub);
	}
	if (keycode == A)
	{
		cub->p->mini_x += cub->p->coef_we.x * SPEED_MINI;
		cub->p->mini_y += cub->p->coef_we.y * SPEED_MINI;
		move_player(cub);
	}
	if (keycode == D)
	{
		cub->p->mini_x -= cub->p->coef_we.x * SPEED_MINI;
		cub->p->mini_y -= cub->p->coef_we.y * SPEED_MINI;
		move_player(cub);
	}
	if (keycode == L_ARROW)
	{
		new_angle(cub, -1);
		move_player(cub);
	}
	if (keycode == R_ARROW)
	{
		new_angle(cub, 1);
		move_player(cub);
	}
	// printf("player angle: %d%%\n", cub->p->angle);
	if (keycode == M)
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
	return (1);
}

void	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	cub->imgs = malloc(sizeof(t_imgs));
	cub->imgs->show_mini = 1;
		
	generate_background(cub);
	generate_minimap(cub);
	generate_player(cub);

	mlx_hook(cub->win, 2, 1l << 0, check_keycode, cub);
	mlx_hook(cub->win, 17, 1l << 0, ft_exit, cub);
	mlx_loop(cub->mlx);
}
