/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:20:01 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/07/27 17:26:12 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_var(t_cub *cub)
{
	cub->mlx = NULL;
	cub->win = NULL;
	cub->map = NULL;
	cub->p = NULL;
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

double	get_angle(double angle, int rotation)
{
	angle += rotation;
	if (angle > 359)
		angle -= 360;
	else if (angle < 0)
		angle += 360;
	return (angle);
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
		find_wall(cub, cub->p->ray[i]->coef_ns, 1, i);
	}
	return (1);
}

int	parsing_map(t_cub *cub, char **argv)
{
	init_var(cub);
	if (is_extension_valid(argv[1], ".cub") != 0)
		return (free(cub), display_error(argv[1], 1));
	if (init_file(cub, argv[1]) != 0)
		return (free(cub), -1);
	if (init_texture(cub) != 0)
		return (exit_cub(cub, 0));
	if (init_map(cub, argv) != 0)
		return (exit_cub(cub, 0));
	if (init_player(cub) != 0)
		return (exit_cub(cub, 0));
	if (!init_color(cub))
		return (exit_cub(cub, 0));
	return (0);
}
