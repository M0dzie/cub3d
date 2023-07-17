/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:20:01 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/07/17 17:37:36 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	destroy_xpm(t_cub *cub)
{
	if (cub->game.img)
		mlx_destroy_image(cub->mlx, cub->game.img);
	if (cub->north.px)
		free(cub->north.px);
	if (cub->south.px)
		free(cub->south.px);
	if (cub->east.path)
		free(cub->east.px);
	if (cub->west.path)
		free(cub->west.px);
}

static void	free_path(t_cub *cub)
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

static void	free_player(t_cub *cub)
{
	int	i;

	i = -1;
	if (cub->p)
	{
		while (++i < WIN_WIDTH)
			free(cub->p->ray[i]);
		free(cub->p->ray);
		free(cub->p);
	}
}

int	exit_cub(t_cub *cub, int xpm)
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
	if (xpm)
		destroy_xpm(cub);
	free_path(cub);
	free_player(cub);
	if (cub->mlx)
	{
		if (cub->win)
			mlx_destroy_window(cub->mlx, cub->win);
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	return (free(cub), exit(0), 0);
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
	return (0);
}
