/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:11:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/25 11:23:53 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

static int	ft_exit(void)
{
	exit(0);
	return (1);
}

static int	check_keycode(int keycode)
{
	if (keycode == ESC)
		ft_exit();
	// if (keycode == W)
	// 	y -= 5;
	// if (keycode == S)
	// 	y += 5;
	// if (keycode == A)
	// 	x -= 5;
	// if (keycode == D)
	// 	x += 5;
	return (1);
}

void	init_mlx(t_mlx *mlx, t_map *map)
{
	(void) map;
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, 2048, 1024, "cub3d");
	mlx_hook(mlx->win, 2, 1l << 0, check_keycode, mlx);
	mlx_hook(mlx->win, 17, 1l << 0, ft_exit, mlx);
	mlx_loop(mlx->ptr);
}
