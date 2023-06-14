/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:19:40 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/14 16:53:35 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

/*
	Une couleur par mur (une nuance de la couleur deja utilisee pour qu'a l'oeil
nu ca ne change rien)

	Define les couleurs par side NORTH SOUTH EAST WEST

	Defiler les rayons qui ont le meme side pour nous donner les murs complets a render ?
*/