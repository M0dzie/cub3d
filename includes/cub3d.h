/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:20:01 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/05/23 17:56:09 by mehdisapin       ###   ########.fr       */
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

int	are_rgb_valid(t_cub *cub);
int	check_border(t_cub *cub);
int	display_error(char *name, int num_error);
int	display_error_texture(t_cub *cub);
int	init_file(t_cub *cub, char *file_name);
int	init_map(t_cub *cub, char **argv);
int	init_texture(t_cub *cub);
int	parsing_map(t_cub *cub, char **argv);

void	free_cub(t_cub *cub);

#endif