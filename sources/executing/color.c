/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:43:40 by thmeyer           #+#    #+#             */
/*   Updated: 2023/06/10 20:53:59 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/thomas.h"

static char	*int_to_hexa(int rgb, char *base, int red)
{
	char 	*hexa;
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

	red = int_to_hexa(rgb[0], base, 1);
	green = int_to_hexa(rgb[1], base, 0);
	blue = int_to_hexa(rgb[2], base, 0);
	if (!red || !green || !blue)
		return (free(red), free(green), free(blue), \
		display_error("red, blue, green", 4), NULL);
	hexa = ft_calloc(9, sizeof(char));
	if (!hexa)
		return (display_error("hexa", 4), NULL);
	hexa = ft_strjoin(red, green);
	hexa = ft_strjoin(hexa, blue);
	if (!hexa)
		return (display_error("hexa", 4), NULL);
	// printf("%s\n", hexa);
	return (free(red), free(green), free(blue), hexa);
}

int	put_rgb(t_data *data, int x, int y, char *rgb)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	if (*(unsigned int *)dst == 0x00202020)
		return (0);
	*(unsigned int *)dst = *(unsigned int *)rgb;
	// printf("char = %s and int = %u\n", dst, *(unsigned int *)dst);
	return (1);
}

int	init_color(t_cub *cub)
{
	int	success;

	success = 0;
	cub->roof = rgb_to_hexa(cub->rgb_roof, "0123456789ABCDEF");
	cub->floor = rgb_to_hexa(cub->rgb_floor, "0123456789ABCDEF");
	if (cub->roof && cub->floor)
		success = 1;
	return (success);
}
