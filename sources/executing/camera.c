/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:29:51 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/06 16:18:47 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

void	init_camera(t_cub *cub)
{
	(void)	cub;
	t_ray	*ray;

	ray = malloc(sizeof(t_ray) * 60 + 1);
	// ray = malloc(sizeof(t_ray) * WIN_WIDTH + 1);
	if (!ray)
		return ;
}