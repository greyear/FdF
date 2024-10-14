/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:32:00 by azinchen          #+#    #+#             */
/*   Updated: 2024/10/09 18:28:49 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

int	mix_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

t_color fake_color(void)
{
	t_color	res;

	res.r = -1;
	res.g = -1;
	res.b = -1;
	res.a = -1;
	return (res);
}

t_color white_color(void)
{
	t_color	res;

	res.r = 255;
	res.g = 255;
	res.b = 255;
	res.a = 255;
	return (res);
}

t_color	set_color_to_height(int z, int max_z, int min_z)
{
	t_color	res;

	if (max_z == min_z)
		res = white_color();
	else
	{
		res.r = 0 + (255 - 0) / (max_z - min_z) * (z - min_z);
		res.g = 128;
		res.b = 0 + (255 - 0) / (max_z - min_z) * (z - min_z);
		res.a = 255;
	}
	return (res);
}

t_color	color_between(t_px start, t_px cur, t_px end)
{
	int		d_small;
	int		d_big;
	t_color	res;

	d_small = abs(cur.x - start.x) + abs(cur.y - start.y);
	d_big = abs(end.x - start.x) + abs(end.y - start.y);
	res.r = start.color.r + ((end.color.r - start.color.r) * d_small) / d_big;
	res.g = start.color.g + ((end.color.g - start.color.g) * d_small) / d_big;
	res.b = start.color.b + ((end.color.b - start.color.b) * d_small) / d_big;
	res.a = start.color.a + ((end.color.a - start.color.a) * d_small) / d_big;
	return (res);
}

int	color_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}
