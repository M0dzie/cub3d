/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:20:01 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/06/07 17:34:08 by msapin           ###   ########.fr       */
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

void	parse_ray(t_cub *cub)
{
	(void)cub;

}

void	parse_player_angle(t_cub *cub, char c)
{
	if (c == 'N')
		cub->p->pos.angle = 0;
	else if (c == 'S')
		cub->p->pos.angle = 180;
	else if (c == 'W')
		cub->p->pos.angle = 270;
	else if (c == 'E')
		cub->p->pos.angle = 90;
	cub->p->pos.coef_ns.x = sin(cub->p->pos.angle * M_PI / 180);
	cub->p->pos.coef_ns.y = -cos(cub->p->pos.angle * M_PI / 180);
	cub->p->pos.coef_we.x = sin((cub->p->pos.angle - 90) * M_PI / 180);
	cub->p->pos.coef_we.y = -cos((cub->p->pos.angle - 90) * M_PI / 180);

	cub->p->pos.coef_nwse.x = sin((cub->p->pos.angle - 45) * M_PI / 180);
	cub->p->pos.coef_nwse.y = -cos((cub->p->pos.angle - 45) * M_PI / 180);

	cub->p->pos.coef_nesw.x = sin((cub->p->pos.angle - 135) * M_PI / 180);
	cub->p->pos.coef_nesw.y = -cos((cub->p->pos.angle - 135) * M_PI / 180);
	
	parse_ray(cub);
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
				parse_player_angle(cub, c);
				cub->p->pos.start.x = j * GRID_MINI;
				cub->p->pos.start.y = i * GRID_MINI;
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
	return (0);
}
