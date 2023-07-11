/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:20:01 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/07/11 10:26:09 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

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

int	calcul_coef(t_cub *cub)
{
	int		i;
	double	tmp_angle;

	cub->p->pos.coef_ns.x = sin(cub->p->pos.angle * M_PI / 180);
	cub->p->pos.coef_ns.y = -cos(cub->p->pos.angle * M_PI / 180);
	cub->p->pos.coef_we.x = sin((cub->p->pos.angle - 90) * M_PI / 180);
	cub->p->pos.coef_we.y = -cos((cub->p->pos.angle - 90) * M_PI / 180);
	cub->p->pos.coef_nwse.x = sin((cub->p->pos.angle - 45) * M_PI / 180);
	cub->p->pos.coef_nwse.y = -cos((cub->p->pos.angle - 45) * M_PI / 180);
	cub->p->pos.coef_nesw.x = sin((cub->p->pos.angle - 135) * M_PI / 180);
	cub->p->pos.coef_nesw.y = -cos((cub->p->pos.angle - 135) * M_PI / 180);
	tmp_angle = get_angle(cub->p->pos.angle - FOV / 2, 0);
	i = -1;
	while (++i < WIN_WIDTH)
	{
		cub->p->ray[i]->angle = get_angle(tmp_angle + ((i + 1) * cub->p->coef), \
		0);
		cub->p->ray[i]->coef_ns.x = sin(cub->p->ray[i]->angle * M_PI / 180);
		cub->p->ray[i]->coef_ns.y = -cos(cub->p->ray[i]->angle * M_PI / 180);
		distance_to_wall(cub, cub->p->ray[i]->coef_ns, 1, i + 1);
	}
	return (1);
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
}

int	malloc_player(t_cub *cub)
{
	int	i;

	cub->p = malloc(sizeof(t_player));
	if (!cub->p)
		return (display_error("cub->p", 4));
	cub->p->ray = ft_calloc(WIN_WIDTH + 1, sizeof(t_ray_map *));
	if (!cub->p->ray)
		return (display_error("cub->p->ray", 4));
	i = -1;
	while (++i < WIN_WIDTH)
	{
		cub->p->ray[i] = malloc(sizeof(t_ray_map));
		if (!cub->p->ray[i])
			return (display_error("cub->p->ray[i]", 4));
	}
	return (0);
}

void	init_pos(t_cub *cub, char side)
{
	cub->cos_angle = cos(SPEED_ANGLE);
	cub->sin_angle = sin(SPEED_ANGLE);
	if (side == 'N')
	{
		cub->p->dir.x = 0.0;
		cub->p->dir.y = -1.0;
		cub->p->dir_ew.x = -1.0;
		cub->p->dir_ew.y = 0.0;
		cub->p->fov.x = -0.66;
		cub->p->fov.y = 0.0;
	}
	else if (side == 'S')
	{
		cub->p->dir.x = 0.0;
		cub->p->dir.y = 1.0;
		cub->p->dir_ew.x = 1.0;
		cub->p->dir_ew.y = 0.0;
		cub->p->fov.x = 0.66;
		cub->p->fov.y = 0.0;
	}
	else if (side == 'W')
	{
		cub->p->dir.x = -1.0;
		cub->p->dir.y = 0.0;
		cub->p->dir_ew.x = 0.0;
		cub->p->dir_ew.y = 1.0;
		cub->p->fov.x = 0.0;
		cub->p->fov.y = 0.66;
	}
	else if (side == 'E')
	{
		cub->p->dir.x = 1.0;
		cub->p->dir.y = 0.0;
		cub->p->dir_ew.x = 0.0;
		cub->p->dir_ew.y = -1.0;
		cub->p->fov.x = 0.0;
		cub->p->fov.y = -0.66;
	}
}

int	init_player(t_cub *cub)
{
	int		i;
	int		j;
	char	c;

	if (malloc_player(cub) != 0)
		return (-1);
	cub->p->coef = FOV / WIN_WIDTH;
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
				cub->p->pos_3d.x = j + 0.5;
				cub->p->pos_3d.y = i + 0.5;
				init_pos(cub, c);
			}
		}
	}
	return (0);
}

void	init_var(t_cub *cub)
{
	cub->mlx = NULL;
	cub->win = NULL;
	cub->imgs = NULL;
	cub->map = NULL;
	cub->p = NULL;
}

int	parsing_map(t_cub *cub, char **argv)
{
	init_var(cub);
	if (is_extension_valid(argv[1], ".cub") != 0)
		return (free(cub), display_error(argv[1], 1));
	if (init_file(cub, argv[1]) != 0)
		return (free(cub), -1);
	if (init_texture(cub) != 0)
		return (exit_cub(cub), -1);
	if (init_map(cub, argv) != 0)
		return (exit_cub(cub), -1);
	if (init_player(cub) != 0)
		return (exit_cub(cub), -1);
	if (!init_color(cub))
		return (exit_cub(cub), -1);
	return (0);
}
