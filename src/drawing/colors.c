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

int	is_colorful_input(t_iso_mtx matrix)
{
	int	i;
	int	j;

	i = 0;
	while (i < matrix.width)
	{
		j = 0;
		while (j < matrix.height)
		{
			if (is_fake(matrix.map[j][i].color) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

t_color	for_colorful_or_not(t_iso p, t_draw *pic)
{
	t_color	c;

	if (pic->colorful == 1)
	{
		if (is_fake(p.color) == 1)
			c = white_color();
		else
			c = p.color;
	}
	else
		c = set_color_to_height(p.or_z, pic->ext.b_z, pic->ext.s_z);
	return (c);
}
