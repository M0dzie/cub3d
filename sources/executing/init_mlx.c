/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:11:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/25 16:27:35 by msapin           ###   ########.fr       */
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
	if (keycode == ESC)
		ft_exit();
	if (keycode == W)
	{
		// printf("W pressed\n");
		// y -= 5;
		move_player(cub);
	}
	if (keycode == S)
	{
		// printf("S pressed\n");
		// y += 5;
		move_player(cub);
	}
	if (keycode == A)
	{
		// printf("A pressed\n");
		// x -= 5;
		move_player(cub);
	}
	if (keycode == D)
	{
		// printf("D pressed\n");
		// x += 5;
		move_player(cub);
	}
	return (1);
}

void	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	cub->imgs = malloc(sizeof(t_imgs));
		
	generate_minimap(cub);

	mlx_hook(cub->win, 2, 1l << 0, check_keycode, cub);
	mlx_hook(cub->win, 17, 1l << 0, ft_exit, cub);
	mlx_loop(cub->mlx);
}
