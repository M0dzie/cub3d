/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_error_texture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:17:04 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/07/31 20:55:49 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	display_path(t_cub *cub, char *id, char *str)
{
	int		i;
	char	**line_split;

	i = -1;
	while (cub->file_split[++i] && i < 6)
	{
		line_split = ft_split(cub->file_split[i], ' ');
		if (ft_strmatch(line_split[0], id))
		{
			ft_putstr_fd(str, 2);
			ft_putendl_fd(line_split[1], 2);
		}
		ft_arrfree(line_split);
	}
}

void	display_missing_texture(t_cub *cub)
{
	ft_putstr_fd("missing texture line:\n\n", 2);
	if (cub->north.fd == 0)
		ft_putstr_fd("north:  NO ./path_to_the_north_texture\n", 2);
	if (cub->south.fd == 0)
		ft_putstr_fd("south:  SO ./path_to_the_south_texture\n", 2);
	if (cub->west.fd == 0)
		ft_putstr_fd("west:   WE ./path_to_the_west_texture\n", 2);
	if (cub->east.fd == 0)
		ft_putstr_fd("east:   EA ./path_to_the_east_texture\n", 2);
}

void	display_invalid_texture(t_cub *cub)
{
	ft_putstr_fd("no such texture file:\n\n", 2);
	if (cub->north.fd < 0)
		display_path(cub, "NO", "north:  NO ");
	if (cub->south.fd == -1)
		display_path(cub, "SO", "south:  SO ");
	if (cub->west.fd == -1)
		display_path(cub, "WE", "west:   WE ");
	if (cub->east.fd == -1)
		display_path(cub, "EA", "east:   EA ");
}

void	display_invalid_rgb(t_cub *cub)
{
	if (!cub->rgb_floor || !cub->rgb_roof)
		ft_putstr_fd("missing rgb color:\n\n", 2);
	if (!cub->rgb_floor)
		ft_putstr_fd("floor:  F 0,125,255    range [0->255]\n", 2);
	if (!cub->rgb_roof)
		ft_putstr_fd("roof:   C 255,125,0    range [0->255]\n", 2);
}

int	display_error_texture(t_cub *cub)
{
	if (cub->north.fd <= 0 || cub->south.fd <= 0 || cub->west.fd <= 0 \
	|| cub->east.fd <= 0 || !cub->rgb_floor || !cub->rgb_roof)
		ft_putstr_fd("Error\n", 2);
	if (cub->north.fd == 0 || cub->south.fd == 0 || cub->west.fd == 0 \
	|| cub->east.fd == 0)
		display_missing_texture(cub);
	if (cub->north.fd < 0 || cub->south.fd < 0 || cub->west.fd < 0 \
	|| cub->east.fd < 0)
		display_invalid_texture(cub);
	if ((cub->north.fd <= 0 || cub->south.fd <= 0 || cub->west.fd <= 0 \
	|| cub->east.fd <= 0) && (!cub->rgb_floor || !cub->rgb_roof))
		ft_putstr_fd("\n", 2);
	if (!are_rgb_valid(cub))
		return (-1);
	display_invalid_rgb(cub);
	if (cub->north.fd <= 0 || cub->south.fd <= 0 || cub->west.fd <= 0 \
	|| cub->east.fd <= 0 || !cub->rgb_floor || !cub->rgb_roof)
		return (-1);
	return (0);
}
