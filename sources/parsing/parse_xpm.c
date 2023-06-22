/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_xpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:36:13 by msapin            #+#    #+#             */
/*   Updated: 2023/06/22 12:32:52 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	save_texture(int *fd, char *path, char **path_save)
{
	*fd = open(path, O_RDONLY);
	if (!*path_save)
		*path_save = ft_strdup(path);
}

void	display_error_xpm(t_cub *cub)
{
	ft_putstr_fd("Error\ninvalid xpm file:\n\n", 2);
	if (!cub->north.tex)
		ft_putendl_fd(cub->north.path, 2);
	if (!cub->south.tex)
		ft_putendl_fd(cub->south.path, 2);
	if (!cub->west.tex)
		ft_putendl_fd(cub->west.path, 2);
	if (!cub->east.tex)
		ft_putendl_fd(cub->east.path, 2);
}

int	parse_xpm(t_cub *cub)
{
	cub->north.tex = mlx_xpm_file_to_image(cub->mlx, cub->north.path, &cub->north.width, &cub->north.height);
	cub->south.tex = mlx_xpm_file_to_image(cub->mlx, cub->south.path, &cub->south.width, &cub->south.height);
	cub->west.tex = mlx_xpm_file_to_image(cub->mlx, cub->west.path, &cub->west.width, &cub->west.height);
	cub->east.tex = mlx_xpm_file_to_image(cub->mlx, cub->east.path, &cub->east.width, &cub->east.height);
	// mlx_put_image_to_window(cub->mlx, cub->win, cub->north.tex, 0, 0);
	// if (!cub->north.tex || !cub->south.tex || !cub->west.tex || !cub->east.tex)
	// 	return (display_error_xpm(cub), -1);
	return (0);
}
