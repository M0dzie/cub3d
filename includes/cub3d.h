/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:20:01 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/05/22 15:13:26 by msapin           ###   ########.fr       */
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
	// fds textures, found if better to use fd int or string as path
	int	fd_north;
	int	fd_south;
	int	fd_west;
	int	fd_east;

	int 			*rgb_floor;
	int 			*rgb_roof;
	char			*file;
	char			**file_split;
	struct s_map	*map;
}					t_cub;

#endif