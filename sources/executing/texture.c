/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:19:40 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/27 00:30:29 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_side_wall(t_cub *cub, t_data *minimap, int ray)
{
	char	*dst;

	dst = minimap->addr + (((int)cub->p->ray[ray]->wall.y - 1) * minimap->line_length + \
	((int)cub->p->ray[ray]->wall.x + (GRID / 2)) * (minimap->bits_per_pixel / 8));
	cub->p->ray[ray]->side = *(unsigned int *)dst;
}
