/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:59:47 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/26 19:32:52 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

int	check_keycode(int keycode, t_cub *cub);
int	ft_exit(void);

static void	display_map(t_map *map)
{
	for (int i = 0; i < map->height; i++)
		printf("%s\n", map->array[i]);
}

// static void	raycaster(t_cub *cub)
// {
// 	cub->mlx = mlx_init();
// 	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");

// 	mlx_hook(cub->win, 2, 1l << 0, check_keycode, cub);
// 	mlx_hook(cub->win, 17, 1l << 0, ft_exit, cub);
// 	mlx_loop(cub->mlx);
// }

void	where_am_i(t_cub *cub)
{
	printf("case : x = %d and y = %d\npixels : x = %d and y = %d\n", \
	cub->p->pos_x, cub->p->pos_y, cub->p->mini_x, cub->p->mini_y);	
}

void	init_raycasting(t_cub *cub)
{
	(void)display_map;

	// raycaster(cub);
	init_mlx(cub);
}