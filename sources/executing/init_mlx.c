/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:11:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/25 23:04:21 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
// #include "../../includes/thomas.h"

static int	ft_exit(void)
{
	exit(0);
	return (1);
}

static int	check_keycode(int keycode, t_cub *cub)
{
	// printf("key pressed :%d\n", keycode);
	if (keycode == ESC)
		ft_exit();
	if (keycode == W)
	{
		// printf("W pressed\n");
		cub->p->mini_y -= SPEED_MINI;
		move_player(cub);
	}
	if (keycode == S)
	{
		// printf("S pressed\n");
		cub->p->mini_y += SPEED_MINI;
		move_player(cub);
	}
	if (keycode == A)
	{
		// printf("A pressed\n");
		cub->p->mini_x -= SPEED_MINI;
		move_player(cub);
	}
	if (keycode == D)
	{
		// printf("D pressed\n");
		cub->p->mini_x += SPEED_MINI;
		move_player(cub);
	}
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
