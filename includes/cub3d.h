/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:20:01 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/05/21 17:05:27 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft/includes/libft.h"
# include <stdio.h>

typedef struct s_map
{
	char	**array;
	int		width;
	int		height;
}			t_map;

typedef struct s_cub
{
	// fds for textures
	int	fd_north;
	int	fd_south;
	int	fd_west;
	int	fd_east;

	// rgb color, found if better to use int tab or string
	int *rgb_floor;
	int *rgb_roof;

	// structure for map
	struct s_map	*map;

	// tmp file
	char	*file;
}					t_cub;

#endif