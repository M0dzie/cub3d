/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:15:35 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/07/21 15:42:37 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_file(t_cub *cub, char *file_name)
{
	int	fd_file;

	fd_file = open(file_name, O_RDONLY);
	if (fd_file < 0)
		return (display_error(file_name, 2));
	cub->file = get_file(fd_file);
	if (!cub->file)
		return (close(fd_file), display_error(file_name, 5));
	return (close(fd_file), 0);
}

static int	*rgb_to_int(char *rgb)
{
	int		i;
	int		nb_commas;
	int		*int_array;
	char	**tmp_split;

	i = -1;
	nb_commas = 0;
	while (rgb[++i])
		if (rgb[i] == ',')
			nb_commas++;
	if (nb_commas != 2 || !is_valid_number(rgb))
		return (NULL);
	tmp_split = ft_split(rgb, ',');
	if (ft_arrlen(tmp_split) != 3)
		return (ft_arrfree(tmp_split), NULL);
	int_array = ft_calloc(3, sizeof(int));
	if (!int_array)
		return (ft_arrfree(tmp_split), display_error("int_array", 4), NULL);
	int_array[0] = ft_atoi(tmp_split[0]);
	int_array[1] = ft_atoi(tmp_split[1]);
	int_array[2] = ft_atoi(tmp_split[2]);
	return (ft_arrfree(tmp_split), int_array);
}

static int	get_texture(t_cub *cub, char *id, char *path)
{
	if (ft_strmatch(id, "NO"))
		save_texture(&cub->north.fd, path, &cub->north.path);
	else if (ft_strmatch(id, "SO"))
		save_texture(&cub->south.fd, path, &cub->south.path);
	else if (ft_strmatch(id, "WE"))
		save_texture(&cub->west.fd, path, &cub->west.path);
	else if (ft_strmatch(id, "EA"))
		save_texture(&cub->east.fd, path, &cub->east.path);
	else if (ft_strmatch(id, "F"))
	{
		if (cub->rgb_floor)
			return (-1);
		cub->rgb_floor = rgb_to_int(path);
	}
	else if (ft_strmatch(id, "C"))
	{
		if (cub->rgb_roof)
			return (-1);
		cub->rgb_roof = rgb_to_int(path);
	}
	else
		return (-1);
	return (0);
}

static void	init_fds(t_cub *cub)
{
	cub->north.fd = 0;
	cub->south.fd = 0;
	cub->west.fd = 0;
	cub->east.fd = 0;
	cub->north.path = NULL;
	cub->south.path = NULL;
	cub->west.path = NULL;
	cub->east.path = NULL;
	cub->north.tex = NULL;
	cub->south.tex = NULL;
	cub->west.tex = NULL;
	cub->east.tex = NULL;
	cub->rgb_floor = NULL;
	cub->rgb_roof = NULL;
	cub->map = NULL;
}



// int	init_file(t_cub *cub, char *file_name)
// {
// 	int	fd_file;

// 	fd_file = open(file_name, O_RDONLY);
// 	if (fd_file < 0)
// 		return (display_error(file_name, 2));
// 	cub->file = get_file(fd_file);
// 	if (!cub->file)
// 		return (close(fd_file), display_error(file_name, 5));
// 	return (close(fd_file), 0);
// }

// int	*rgb_to_int(char *rgb)
// {
// 	int		*int_array;
// 	char	**tmp_split;

// 	tmp_split = ft_split(rgb, ',');
// 	if (ft_arrlen(tmp_split) != 3)
// 		return (ft_arrfree(tmp_split), NULL);
// 	int_array = ft_calloc(4, sizeof(int));
// 	if (!int_array)
// 		return (ft_arrfree(tmp_split), display_error("int_array", 4), NULL);
// 	int_array[0] = ft_atoi(tmp_split[0]);
// 	int_array[1] = ft_atoi(tmp_split[1]);
// 	int_array[2] = ft_atoi(tmp_split[2]);
// 	return (ft_arrfree(tmp_split), int_array);
// }

// static int	get_texture(t_cub *cub, char *id, char *path)
// {
// 	if (ft_strmatch(id, "NO"))
// 		cub->fd_north = open(path, O_RDONLY);
// 	else if (ft_strmatch(id, "SO"))
// 		cub->fd_south = open(path, O_RDONLY);
// 	else if (ft_strmatch(id, "WE"))
// 		cub->fd_west = open(path, O_RDONLY);
// 	else if (ft_strmatch(id, "EA"))
// 		cub->fd_east = open(path, O_RDONLY);
// 	else if (ft_strmatch(id, "F"))
// 		cub->rgb_floor = rgb_to_int(path);
// 	else if (ft_strmatch(id, "C"))
// 		cub->rgb_roof = rgb_to_int(path);
// 	else
// 		return (-1);
// 	return (0);
// }

// static void	init_fds(t_cub *cub)
// {
// 	cub->fd_north = 0;
// 	cub->fd_south = 0;
// 	cub->fd_west = 0;
// 	cub->fd_east = 0;
// 	cub->rgb_floor = NULL;
// 	cub->rgb_roof = NULL;
// 	cub->map = NULL;
// }

// int	init_texture(t_cub *cub)
// {
// 	char	**line_split;
// 	int		i;

/*// 	init_fds(cub);
// 	cub->file_split = ft_split(cub->file, '\n');
// 	i = -1;
// 	while (cub->file_split[++i] && cub->file_split[i][0] != '1' && i < 6)
// 	{
// 		line_split = ft_split(cub->file_split[i], ' ');
// 		if (ft_arrlen(line_split) != 2)
// 			return (ft_arrfree(line_split), \
// 			display_error(cub->file_split[i], 7));
// 		if (get_texture(cub, line_split[0], line_split[1]) != 0)
// 		{
// 			ft_arrfree(line_split);
// 			break ;
// 		}
// 		else
// 			ft_arrfree(line_split);
// 	}
// 	if (display_error_texture(cub) != 0)
// 		return (-1);
// 	return (0);
// }*/

int	init_texture(t_cub *cub)
{
	char	**line_split;
	int		i;

	init_fds(cub);
	cub->file_split = ft_split(cub->file, '\n');
	i = -1;
	while (cub->file_split[++i] && cub->file_split[i][0] != '1' && i < 6)
	{
		line_split = ft_split(cub->file_split[i], ' ');
		if (ft_arrlen(line_split) != 2)
			return (ft_arrfree(line_split), \
			display_error(cub->file_split[i], 7));
		if (get_texture(cub, line_split[0], line_split[1]) != 0)
		{
			ft_arrfree(line_split);
			break ;
		}
		else
			ft_arrfree(line_split);
	}
	if (display_error_texture(cub) != 0)
		return (-1);
	return (0);
}
