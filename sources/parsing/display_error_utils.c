/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_error_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:39:18 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/05/23 17:54:26 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	display_error_rgb(int validity)
{
	if (validity > 0)
		ft_putstr_fd("Error\ninvalid rgb format:\n\n", 2);
	if (validity == 1)
		ft_putstr_fd("expected: F 0,125,255    range [0->255]\n", 2);
	else if (validity == 2)
		ft_putstr_fd("expected: C 255,125,0    range [0->255]\n", 2);
	else if (validity == 3)
	{
		ft_putstr_fd("expected: F 0,125,255    range [0->255]\n", 2);
		ft_putstr_fd("          C 255,125,0    range [0->255]\n", 2);
	}
	if (validity > 0)
		return (0);
	return (-1);
}

int	are_rgb_valid(t_cub *cub)
{
	int	i;
	int	validity;

	i = -1;
	validity = 0;
	while (++i < 3 && cub->rgb_floor)
	{
		if (cub->rgb_floor[i] < 0 || cub->rgb_floor[i] > 255)
		{
			validity = 1;
			break ;
		}
	}
	i = -1;
	while (++i < 3 && cub->rgb_roof)
	{
		if (!cub->rgb_roof || cub->rgb_roof[i] < 0 || cub->rgb_roof[i] > 255)
		{
			validity += 2;
			break ;
		}
	}
	return (display_error_rgb(validity));
}
