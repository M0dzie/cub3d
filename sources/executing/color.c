/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:43:40 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/04 22:17:54 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

static char	*int_to_hexa(int rgb, char *base, int red)
{
	char	*hexa;
	int		div;
	int		mod;
	int		i;

	i = 0;
	if (red)
		hexa = ft_calloc(5, sizeof(char));
	else
		hexa = ft_calloc(3, sizeof(char));
	if (!hexa)
		return (display_error("hexa", 4), NULL);
	div = rgb / 16;
	mod = rgb % 16;
	if (red)
	{
		hexa[i++] = '0';
		hexa[i++] = 'x';
	}
	hexa[i] = base[div];
	hexa[i + 1] = base[mod];
	return (hexa);
}

static char	*rgb_to_hexa(int *rgb, char *base)
{
	char	*red;
	char	*green;
	char	*blue;
	char	*hexa;
	char	*tmp;

	red = int_to_hexa(rgb[0], base, 1);
	green = int_to_hexa(rgb[1], base, 0);
	blue = int_to_hexa(rgb[2], base, 0);
	if (!red || !green || !blue)
		return (free(red), free(green), free(blue), \
		display_error("red, blue, green", 4), NULL);
	tmp = ft_strjoin(red, green);
	hexa = ft_strjoin(tmp, blue);
	free(tmp);
	if (!hexa)
		return (display_error("hexa", 4), NULL);
	return (free(red), free(green), free(blue), hexa);
}

static int	hexa_to_int(const char *rgb)
{
	int	result;
	int	digit_value;
	int	i;
	int	power;

	i = 1;
	result = 0;
	digit_value = 0;
	power = 5;
	while (rgb[++i])
	{
		if (rgb[i] >= '0' && rgb[i] <= '9')
			digit_value = rgb[i] - '0';
		else if (rgb[i] >= 'A' && rgb[i] <= 'F')
			digit_value = rgb[i] - 'A' + 10;
		result += (digit_value * pow(16, power));
		power--;
	}
	return (result);
}

int	init_color(t_cub *cub)
{
	char	*roof;
	char	*floor;
	int		success;

	success = 0;
	roof = rgb_to_hexa(cub->rgb_roof, "0123456789ABCDEF");
	floor = rgb_to_hexa(cub->rgb_floor, "0123456789ABCDEF");
	cub->roof = hexa_to_int(roof);
	cub->floor = hexa_to_int(floor);
	if (cub->roof >= 0 && cub->floor >= 0)
		success = 1;
	return (free(roof), free(floor), success);
}
