/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:29:51 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/06 17:05:00 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

static int	find_wall(t_data *data, int x, int y)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    if (*(unsigned int *)dst == 0x00202020)
        return (1);
    return (0);
}

void	init_camera(t_cub *cub, t_data *data)
{
	(void)	cub;
	(void)	data;
	t_ray	**ray;
	int		i;
	int		angle;

	i = 0;
	ray = malloc(sizeof(t_ray *) * (60 + 1));
	// ray = malloc(sizeof(t_ray) * (WIN_WIDTH + 1));
	if (!ray)
		return ;
	while (ray[i])
	{
		if (i == 30)
			angle = 0;
		printf("ray n%d\n", i);
	}
}