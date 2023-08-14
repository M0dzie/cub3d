/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:18:05 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/08/14 17:50:01 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	display_error(char *name, int num_error)
{
	char	*err[16];

	err[0] = ": wrong function call\n\nexpected:  ./cub3D   *.cub";
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
	err[11] = ": invalid character\n\nmust be composed of 0, 1, N, S, E, W \
char only";
	err[12] = ": must have one starting point (N, S, E, W)";
	err[13] = ": must be surrounded by wall";
	err[14] = ": mlx couldn't init";
	err[15] = ": invalid character";
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd(err[num_error], 2);
	return (-1);
}
