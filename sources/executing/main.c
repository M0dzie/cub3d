/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:20:01 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/05/21 22:55:55 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	display_error(char *name, int num_error)
{
	char	*err[13];

	err[0] = ": wrong function call\n\nexpected:  ./cub3d   *.cub";
	err[1] = ": wrong file extension\n\nexpected:   .cub file";
	err[2] = ": no such file or directory";
	err[3] = ": invalid map\n\ncheck:    maps/example.cub";
	err[4] = ": cannot allocate memory";
	err[5] = ": cannot get file";
	err[6] = ": missing texture file";
	err[7] = ": invalid texture line, too many arguments";
	// err[6] = ": invalid map\n\nneed to be surround by wall";
	// err[7] = ": invalid map\n\nmust be composed of 0, 1, C, E, P char only";
	// err[10] = ": cannot initialize mlx";
	// err[11] = ": cannot generate window";
	// err[12] = ": cannot initialize images";
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd(err[num_error], 2);
	return (-1);
}

char	*get_only_name(char *file_name)
{
	char	*tmp_name;
	int		len_name;
	int		i;

	len_name = ft_strlen(file_name);
	tmp_name = ft_calloc(len_name + 1, sizeof(char));
	if (!tmp_name)
		return (NULL);
	i = -1;
	while (++i < len_name)
		tmp_name[i] = file_name[i];
	return (tmp_name);
}

int	is_extension_valid(char *file_name, char *extension)
{
	int		i_last_c;
	int		j_last_c;
	char	*tmp_name;

	tmp_name = ft_strrchr(file_name, '/');
	if (!tmp_name)
		tmp_name = get_only_name(file_name);
	else
	{
		tmp_name = ft_strtrim(tmp_name, "/");
		if (!tmp_name[0])
			return (free(tmp_name), -1);
	}
	j_last_c = 4;
	i_last_c = ft_strlen(tmp_name) - 1;
	if (i_last_c < 4)
		return (free(tmp_name), -1);
	while (--j_last_c >= 0)
	{
		if (tmp_name[i_last_c] != extension[j_last_c])
			return (free(tmp_name), -1);
		i_last_c--;
	}
	return (free(tmp_name), 0);
}

int	fill_map(t_cub *cub, char *file_name)
{
	(void)cub;
	// int		i;
	// char	*line;
	int		fd_file;

	(void)fd_file;
	(void)file_name;
	(void)cub;

	return (0);
}

int	init_map(t_cub *cub)
{
	int	num_error;
	(void)num_error;

	cub->map = malloc(sizeof(t_map));
	if (!cub->map)
		return (4);
	// num_error = fill_map(vars, file_name);
	// if (num_error != 0)
	// 	return (num_error);
	return (0);
}

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

int	get_texture(t_cub *cub, char *id, char *path)
{
	if (ft_strmatch(id, "NO"))
		cub->fd_north = open(path, O_RDONLY);
	if (ft_strmatch(id, "SO"))
		cub->fd_south = open(path, O_RDONLY);
	if (ft_strmatch(id, "WE"))
		cub->fd_west = open(path, O_RDONLY);
	if (ft_strmatch(id, "EA"))
		cub->fd_east = open(path, O_RDONLY);
	if (ft_strmatch(id, "F"))
		printf("floor rgb : %s\n", path);
	if (ft_strmatch(id, "C"))
		printf("roof rgb : %s\n", path);
	return (0);
}

int	display_error_texture(t_cub *cub)
{
	if (!cub->fd_north || !cub->fd_south || !cub->fd_west || !cub->fd_east)
		ft_putstr_fd("Error\nmissing texture file:\n\n", 2);
	if (!cub->fd_north)
		ft_putstr_fd("north:  NO ./path_to_the_north_texture\n", 2);
	if (!cub->fd_south)
		ft_putstr_fd("south:  SO ./path_to_the_south_texture\n", 2);
	if (!cub->fd_west)
		ft_putstr_fd("west:   WE ./path_to_the_west_texture\n", 2);
	if (!cub->fd_east)
		ft_putstr_fd("east:   EA ./path_to_the_east_texture\n", 2);
	if (!cub->fd_north || !cub->fd_south || !cub->fd_west || !cub->fd_east)
		return (ft_putstr_fd("\n", 2), -1);
	return (0);
}

void	init_fds(t_cub *cub)
{
	cub->fd_north = 0;
	cub->fd_south = 0;
	cub->fd_west = 0;
	cub->fd_east = 0;
}

int	init_texture(t_cub *cub)
{
	char	**file_split;
	char	**line_split;
	int		i;

	init_fds(cub);
	file_split = ft_split(cub->file, '\n');
	i = -1;
	while (file_split[++i] && i < 6)
	{
		line_split = ft_split(file_split[i], ' ');
		if (line_split[2])
			return (display_error(file_split[i], 7));
		if (get_texture(cub, line_split[0], line_split[1]) != 0)
			return (-1);
	}
	if (display_error_texture(cub) != 0)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	if (argc <= 1 || argc >= 3)
		return (display_error(argv[0], 0));
	if (is_extension_valid(argv[1], ".cub") != 0)
		return (display_error(argv[1], 1));
	cub = malloc(sizeof(t_cub));
	if (!cub)
		return (display_error("t_cub", 4));
	if (init_file(cub, argv[1]) != 0)
		return (-1);
	if (init_texture(cub) != 0)
		return (-1);
	if (init_map(cub) != 0)
		return (-1);
	return (0);
}
