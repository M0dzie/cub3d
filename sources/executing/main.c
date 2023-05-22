/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:20:01 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/05/22 23:12:15 by mehdisapin       ###   ########.fr       */
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
	err[7] = ": wrong number of arguments";
	err[8] = ": no map description";
	err[9] = ": map not long enough";
	err[10] = ": map not wide enough";
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

void	get_map_dimension(t_cub *cub)
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
	int	num_error;
	(void)num_error;

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

	// printf("height map %d\n", cub->map->height);
	// printf("%s\n", (cub->file_split + 6)[0]);
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

int	*rgb_to_int(char *rgb)
{
	int		*int_array;
	char	**tmp_split;

	tmp_split = ft_split(rgb, ',');
	if (ft_arrlen(tmp_split) != 3)
		return (ft_arrfree(tmp_split), NULL);
	int_array = ft_calloc(4, sizeof(int));
	if (!int_array)
		return (ft_arrfree(tmp_split), display_error("int_array", 4), NULL);
	int_array[0] = ft_atoi(tmp_split[0]);
	int_array[1] = ft_atoi(tmp_split[1]);
	int_array[2] = ft_atoi(tmp_split[2]);
	return (ft_arrfree(tmp_split), int_array);
}

int	get_texture(t_cub *cub, char *id, char *path)
{
	if (ft_strmatch(id, "NO"))
		cub->fd_north = open(path, O_RDONLY);
	else if (ft_strmatch(id, "SO"))
		cub->fd_south = open(path, O_RDONLY);
	else if (ft_strmatch(id, "WE"))
		cub->fd_west = open(path, O_RDONLY);
	else if (ft_strmatch(id, "EA"))
		cub->fd_east = open(path, O_RDONLY);
	else if (ft_strmatch(id, "F"))
		cub->rgb_floor = rgb_to_int(path);
	else if (ft_strmatch(id, "C"))
		cub->rgb_roof = rgb_to_int(path);
	else
		return (-1);
	return (0);
}

int	display_error_rgb(int validity)
{
	if (validity > 0)
		ft_putstr_fd("Error\ninvalid rgb format:\n\n", 2);
	if (validity == 1)
		ft_putstr_fd("expected: F 0,125,255    range [0->255]\n", 2);
	else if (validity == 2)
		ft_putstr_fd("expected: C 255,125,0    range [0->255]\n", 2);
	else if (validity == 3)
	{
		ft_putstr_fd("expected: F 0,125,255    range [0->255]\n", 2);
		ft_putstr_fd("          C 255,125,0    range [0->255]\n", 2);
	}
	if (validity > 0)
		return (0);
	return (-1);
}

int	are_rgb_valid(t_cub *cub)
{
	int	i;
	int	validity;

	i = -1;
	validity = 0;
	while (++i < 3 && cub->rgb_floor)
	{
		if (cub->rgb_floor[i] < 0 || cub->rgb_floor[i] > 255)
		{
			validity = 1;
			break ;
		}
	}
	i = -1;
	while (++i < 3 && cub->rgb_roof)
	{
		if (!cub->rgb_roof || cub->rgb_roof[i] < 0 || cub->rgb_roof[i] > 255)
		{
			validity += 2;
			break ;
		}
	}
	return (display_error_rgb(validity));
}

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
	}
	ft_arrfree(line_split);
}

void	display_missing_texture(t_cub *cub)
{
	ft_putstr_fd("missing texture line:\n\n", 2);
	if (cub->fd_north == 0)
		ft_putstr_fd("north:  NO ./path_to_the_north_texture\n", 2);
	if (cub->fd_south == 0)
		ft_putstr_fd("south:  SO ./path_to_the_south_texture\n", 2);
	if (cub->fd_west == 0)
		ft_putstr_fd("west:   WE ./path_to_the_west_texture\n", 2);
	if (cub->fd_east == 0)
		ft_putstr_fd("east:   EA ./path_to_the_east_texture\n", 2);
}

void	display_invalid_texture(t_cub *cub)
{
	ft_putstr_fd("no such texture file:\n\n", 2);
	if (cub->fd_north == -1)
		display_path(cub, "NO", "north:  NO ");
	if (cub->fd_south == -1)
		display_path(cub, "SO", "south:  SO ");
	if (cub->fd_west == -1)
		display_path(cub, "WE", "west:   WE ");
	if (cub->fd_east == -1)
		display_path(cub, "EA", "east:   EA ");
}

int	display_error_texture(t_cub *cub)
{
	if (cub->fd_north <= 0 || cub->fd_south <= 0 || cub->fd_west <= 0 || cub->fd_east <= 0 || !cub->rgb_floor || !cub->rgb_roof)
		ft_putstr_fd("Error\n", 2);

	if (cub->fd_north == 0 || cub->fd_south == 0 || cub->fd_west == 0 || cub->fd_east == 0)
		display_missing_texture(cub);
	
	if (cub->fd_north < 0 || cub->fd_south < 0 || cub->fd_west < 0 || cub->fd_east < 0)
		display_invalid_texture(cub);

	if ((cub->fd_north <= 0 || cub->fd_south <= 0 || cub->fd_west <= 0 || cub->fd_east <= 0) && (!cub->rgb_floor || !cub->rgb_roof))
		ft_putstr_fd("\n", 2);
	if (!are_rgb_valid(cub))
		return (-1);
	if (!cub->rgb_floor|| !cub->rgb_roof)
		ft_putstr_fd("missing rgb color:\n\n", 2);
	if (!cub->rgb_floor)
		ft_putstr_fd("floor:  F 0,125,255    range [0->255]\n", 2);
	if (!cub->rgb_roof)
		ft_putstr_fd("roof:   C 255,125,0    range [0->255]\n", 2);
	if (cub->fd_north <= 0 || cub->fd_south <= 0 || cub->fd_west <= 0 || cub->fd_east <= 0 || !cub->rgb_floor || !cub->rgb_roof)
		return (-1);
	return (0);
}

void	init_fds(t_cub *cub)
{
	cub->fd_north = 0;
	cub->fd_south = 0;
	cub->fd_west = 0;
	cub->fd_east = 0;
	cub->rgb_floor = NULL;
	cub->rgb_roof = NULL;
	cub->map = NULL;
}

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
			return (ft_arrfree(line_split), display_error(cub->file_split[i], 7));
		if (get_texture(cub, line_split[0], line_split[1]) != 0)
		{
			ft_arrfree(line_split);
			break;
		}
		else
			ft_arrfree(line_split);
		// line_split = NULL;
	}
	// if (line_split)
		// ft_arrfree(line_split);
	if (display_error_texture(cub) != 0)
		return (-1);
	return (0);
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
	if (is_extension_valid(argv[1], ".cub") != 0)
		return (display_error(argv[1], 1));
	cub = malloc(sizeof(t_cub));
	if (!cub)
		return (display_error("t_cub", 4));
	if (init_file(cub, argv[1]) != 0)
		return (free(cub), -1);
	if (init_texture(cub) != 0)
		return (free_cub(cub), -1);
	if (init_map(cub, argv) != 0)
		return (-1);
	return (free_cub(cub), 0);
}
