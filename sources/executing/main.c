/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:20:01 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/05/25 10:16:10 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

void	free_cub(t_cub *cub)
{
	if (cub->rgb_floor)
		free(cub->rgb_floor);
	if (cub->rgb_roof)
		free(cub->rgb_roof);
	if (cub->file)
		free(cub->file);
	ft_arrfree(cub->file_split);
	if (cub->map)
	{
		if (cub->map->array)
			ft_arrfree(cub->map->array);
		free(cub->map);
	}
	free(cub);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	if (argc <= 1 || argc >= 3)
		return (display_error(argv[0], 0));
	cub = malloc(sizeof(t_cub));
	if (!cub)
		return (display_error("t_cub", 4));
	if (parsing_map(cub, argv) != 0)
		return (-1);
	init_raycasting(cub->map);
	return (free_cub(cub), 0);
}
