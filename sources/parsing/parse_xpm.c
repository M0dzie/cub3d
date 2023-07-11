/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_xpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:36:13 by msapin            #+#    #+#             */
/*   Updated: 2023/07/10 19:11:48 by mehdisapin       ###   ########.fr       */
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

int	init_xpm(t_cub *cub, t_xpm *wall)
{
	int	i;
	int	j;
	int	nb_px;

	wall->tex = mlx_xpm_file_to_image(cub->mlx, wall->path, &wall->width, \
	&wall->height);
	if (!wall->tex)
		return (display_error_xpm(cub), -1);
	wall->data = (int *)mlx_get_data_addr(wall->tex, &wall->bits_per_pixel, \
	&wall->line_length, &wall->endian);
	wall->px = ft_calloc(wall->width * wall->height + 1, sizeof(int));
	if (!wall->px)
		return (-1);
	i = -1;
	nb_px = wall->width * wall->height;
	while (++i < nb_px)
		wall->px[i] = 0;
	i = -1;
	while (++i < wall->height)
	{
		j = -1;
		while (++j < wall->width)
			wall->px[wall->width * i + (wall->width - j)] = \
			wall->data[wall->width * i + j];
			/*wall->px[wall->width * i + (j)] = \
			wall->data[wall->width * i + j];*/
	}
	mlx_destroy_image(cub->mlx, wall->tex);
	return (0);
}

int	parse_xpm(t_cub *cub)
{
	if (init_xpm(cub, &cub->north) != 0 || init_xpm(cub, &cub->south) != 0 \
	|| init_xpm(cub, &cub->west) != 0 || init_xpm(cub, &cub->east) != 0)
		return (-1);
	return (0);
}
