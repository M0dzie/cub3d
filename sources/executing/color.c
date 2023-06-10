/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:43:40 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/10 19:27:22 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

char *int_to_hexa(int rgb, char *base, int red)
{
	char 	*hex;
	int		div;
	int		mod;
	int		i;

	i = 0;
	if (red)
		hex = ft_calloc(5, sizeof(char));
	else
		hex = ft_calloc(3, sizeof(char));
	if (!hex)
		return (display_error("hex", 4), NULL);
	div = rgb / 16;
	mod = rgb % 16;
	if (red)
	{
		hex[i++] = '0';
		hex[i++] = 'x';
	}
	hex[i] = base[div];
	hex[i + 1] = base[mod];
	hex[i + 2] = '\0';
	return (hex);
}

void	rgb_to_hexa(t_cub *cub, char *base)
{
	char	*red;
	char	*green;
	char	*blue;
	char	*hex;

	red = int_to_hexa(cub->rgb_floor[0], base, 1);
	green = int_to_hexa(cub->rgb_floor[1], base, 0);
	blue = int_to_hexa(cub->rgb_floor[2], base, 0);
	if (!red || !green || !blue)
		return (display_error("red, blue, green", 4));
}