/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:43:13 by msapin            #+#    #+#             */
/*   Updated: 2023/07/19 18:42:09 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	actions(t_cub *cub)
{
	if (cub->key.w)
		move_player(cub, cub->p->axis, 1);
	if (cub->key.s)
		move_player(cub, cub->p->axis, -1);
	if (cub->key.a)
		move_player(cub, cub->p->axis_side, 1);
	if (cub->key.d)
		move_player(cub, cub->p->axis_side, -1);
	if (cub->key.l_arrow)
		rotate_player(cub, -1);
	if (cub->key.r_arrow)
		rotate_player(cub, 1);
	return (0);
}

int	render_cub3d(t_cub *cub)
{
	actions(cub);
	init_raycasting(cub);
	render_texture(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->game.img, 0, 0);
	return (0);
}

int	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return (1);
}
