/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:19:40 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/23 14:52:22 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"
// #include "../../includes/mlx_linux/mlx_int.h"
// #include "../../includes/mlx/mlx_int.h"

void	init_side_wall(t_cub *cub, t_data *minimap, int ray)
{
	char	*dst;

	dst = minimap->addr + (((int)cub->p->ray[ray]->wall.y - 1) * \
	minimap->line_length + ((int)cub->p->ray[ray]->wall.x + (GRID_MINI / 2)) \
	* (minimap->bits_per_pixel / 8));
	cub->p->ray[ray]->side = *(unsigned int *)dst;
}

int	get_pixel(t_xpm tex, int x, int y)
{
	char	*pixel_color;
	int		color;

	// if (x < 0 || x > tex.width || y < 0 || y > tex.height)
	// 	return (0);
	pixel_color = tex.addr + y * tex.line_length + x * (tex.bits_per_pixel / 8);
	color = *(unsigned int *)pixel_color;
	return (color);
}

// int	get_pixel(t_xpm tex, double percent_face, int line, double wall_height)
// {
// 	int		pixel;
// 	int		x;
// 	int		y;

// 	x = percent_face * tex.width;
//     y = (tex.height * wall_height) / line * tex.width;
//     pixel = x + y;
// }
