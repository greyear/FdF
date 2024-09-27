/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:32:00 by azinchen          #+#    #+#             */
/*   Updated: 2024/09/27 18:34:59 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

int	mix_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

t_color	set_color(int z, int max_z, int min_z)
{
	t_color	res;

	res.r = 0 + (255 - 0) / (max_z - min_z) * (z - min_z);
	res.g = 128;
	res.b = 0 + (255 - 0) / (max_z - min_z) * (z - min_z);
	res.a = 255;

	return (res);
}

t_color	intermediate_color(t_px start, t_px cur, t_px end)
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
