/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_xpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:36:13 by msapin            #+#    #+#             */
/*   Updated: 2023/08/01 10:24:45 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	display_error_xpm(t_cub *cub)
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

static int	init_xpm(t_cub *cub, t_xpm *wall)
{
	wall->tex = mlx_xpm_file_to_image(cub->mlx, wall->path, &wall->width, \
	&wall->height);
	if (!wall->tex)
		return (-1);
	wall->addr = mlx_get_data_addr(wall->tex, &wall->bits_per_pixel, \
	&wall->line_length, &wall->endian);
	return (0);
}

void	save_texture(int *fd, char *path, char **path_save)
{
	*fd = open(path, O_RDONLY);
	if (!*path_save)
		*path_save = ft_strdup(path);
	close(*fd);
}

int	parse_xpm(t_cub *cub)
{
	int	validity;

	validity = 0;
	validity += init_xpm(cub, &cub->north);
	validity += init_xpm(cub, &cub->south);
	validity += init_xpm(cub, &cub->west);
	validity += init_xpm(cub, &cub->east);
	if (validity != 0)
		return (display_error_xpm(cub), -1);
	return (0);
}
