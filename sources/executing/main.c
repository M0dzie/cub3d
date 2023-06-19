/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:20:01 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/06/19 17:44:38 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

void	destroy_xpm(t_cub *cub)
{
	(void)cub;
	
}

void	free_path(t_cub *cub)
{
	if (cub->north.path)
		free(cub->north.path);
	if (cub->south.path)
		free(cub->south.path);
	if (cub->west.path)
		free(cub->west.path);
	if (cub->east.path)
		free(cub->east.path);
}

void	free_cub(t_cub *cub)
{
	if (cub->rgb_floor)
		free(cub->rgb_floor);
	if (cub->rgb_roof)
		free(cub->rgb_roof);
	if (cub->file)
		free(cub->file);
	ft_arrfree(cub->file_split);
	free_path(cub);
	if (cub->map)
	{
		if (cub->map->array)
			ft_arrfree(cub->map->array);
		free(cub->map);
	}
	destroy_xpm(cub);
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
	init_mlx(cub);
	return (free_cub(cub), 0);
}
