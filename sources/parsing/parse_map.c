/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:20:01 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/05/30 19:47:44 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

static int	is_extension_valid(char *file_name, char *extension)
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

static void	init_pos(t_cub *cub, int y, int x)
{
	cub->p->pos.x = x;
	cub->p->pos.y = y;
	if (cub->map->array[y][x] == 'N')
	{
		cub->p->dir.x = 0;
		cub->p->dir.y = -1;
	}
	if (cub->map->array[y][x]  == 'S')
	{
		cub->p->dir.x = 0;
		cub->p->dir.y = 1;
	}
	if (cub->map->array[y][x]  == 'E')
	{
		cub->p->dir.x = 1;
		cub->p->dir.y = 0;
	}
	if (cub->map->array[y][x]  == 'W')
	{
		cub->p->dir.x = -1;
		cub->p->dir.y = 0;
	}
}

int	init_player(t_cub *cub)
{
	int		i;
	int		j;
	char	c;

	cub->p = malloc(sizeof(t_player));
	if (!cub->p)
		return (display_error("cub->p", 4));
	i = -1;
	while (cub->map->array[++i])
	{
		j = -1;
		while (cub->map->array[i][++j])
		{
			c = cub->map->array[i][j];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
			{
				init_pos(cub, i, j);
				cub->p->mini_x = j * GRID_MINI;
				cub->p->mini_y = i * GRID_MINI;
			}
		}
	}
	return (0);
}

int	parsing_map(t_cub *cub, char **argv)
{
	if (is_extension_valid(argv[1], ".cub") != 0)
		return (free(cub), display_error(argv[1], 1));
	if (init_file(cub, argv[1]) != 0)
		return (free(cub), -1);
	if (init_texture(cub) != 0)
		return (free_cub(cub), -1);
	if (init_map(cub, argv) != 0)
		return (free_cub(cub), -1);
	if (init_player(cub) != 0)
		return (free_cub(cub), -1);
	// parse_info(cub);
	return (0);
}
