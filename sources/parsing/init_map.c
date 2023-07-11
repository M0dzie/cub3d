/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:15:32 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/07/11 12:00:32 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	are_char_valid(t_cub *cub)
{
	int		i;
	int		j;
	int		nb_start;
	char	c;

	i = -1;
	nb_start = 0;
	while (cub->map->array[++i])
	{
		j = -1;
		while (cub->map->array[i][++j])
		{
			c = cub->map->array[i][j];
			if (!(c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' \
			|| c == 'W' || c == ' '))
				return (display_error("map", 11), 0);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				nb_start++;
		}
	}
	if (nb_start != 1)
		return (display_error("map", 12), 0);
	return (1);
}

static int	get_map(t_cub *cub)
{
	int		i;

	cub->map->array = ft_calloc(cub->map->height + 1, sizeof(char *));
	if (!cub->map->array)
		return (display_error("cub->map->array", 4));
	i = -1;
	while (++i < cub->map->height)
		cub->map->array[i] = ft_strdup_null(cub->file_split[6 + i]);
	if (!are_char_valid(cub))
		return (-1);
	return (0);
}

static void	get_map_dimension(t_cub *cub)
{
	int	i;
	int	tmp_width;

	cub->map->height = ft_arrlen(cub->file_split + 6);
	i = 5;
	cub->map->width = 0;
	tmp_width = 0;
	while (cub->file_split[++i])
	{
		tmp_width = ft_strlen_null(cub->file_split[i]);
		if (cub->map->width < tmp_width)
			cub->map->width = tmp_width;
	}
}

int	init_map(t_cub *cub, char **argv)
{
	cub->map = malloc(sizeof(t_map));
	if (!cub->map)
		return (display_error("cub->map", 4));
	cub->map->array = NULL;
	if (!cub->file_split[6])
		return (display_error(argv[1], 8));
	get_map_dimension(cub);
	if (cub->map->height < 3)
		return (display_error(argv[1], 9));
	if (cub->map->width < 3)
		return (display_error(argv[1], 10));
	if (get_map(cub) != 0)
		return (-1);
	if (check_border(cub) != 0)
		return (display_error("map", 13));
	return (0);
}
