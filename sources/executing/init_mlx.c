/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:11:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/09 13:04:13 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
// #include "../../includes/thomas.h"

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

static int	check_keycode(int keycode, t_cub *cub)
{
	if (keycode == ESC)
		ft_exit();
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
		set_angle(cub, -1);
		move_player(cub, cub->p->pos.coef_ns, 0);
	}
	if (keycode == R_ARROW)
	{
		set_angle(cub, 1);
		move_player(cub, cub->p->pos.coef_ns, 0);
	}
	// printf("player angle: %d%%\n", cub->p->pos.angle);
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

void	display_images(t_cub *cub)
{
	mlx_put_image_to_window(cub->mlx, cub->win, cub->imgs->back.img, 0, 0);
	if (cub->imgs->show_mini)
	{
		mlx_put_image_to_window(cub->mlx, cub->win, cub->imgs->minimap.img, (WIN_WIDTH / 2) - (cub->map->width * GRID_MINI / 2), (WIN_HEIGHT / 2) - (cub->map->height * GRID_MINI / 2));
	}
}

void	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	cub->imgs = malloc(sizeof(t_imgs));
	cub->imgs->show_mini = 1;
		
	generate_minimap(cub);
	calcul_coef(cub);
	generate_player(cub);
	generate_background(cub);

	display_images(cub);

	mlx_hook(cub->win, 2, 1l << 0, check_keycode, cub);
	mlx_hook(cub->win, 17, 1l << 0, ft_exit, cub);
	mlx_loop(cub->mlx);
}
