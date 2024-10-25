/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_rgba.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:30:58 by azinchen          #+#    #+#             */
/*   Updated: 2024/10/04 17:20:19 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static t_color	extract_eight(int color)
{
	t_color	res;

	res.r = (color >> 24) & 0xFF;
	res.g = (color >> 16) & 0xFF;
	res.b = (color >> 8) & 0xFF;
	res.a = (color) & 0xFF;
	return (res);
}

static t_color	extract_six(int color)
{
	t_color	res;

	res.r = (color >> 16) & 0xFF;
	res.g = (color >> 8) & 0xFF;
	res.b = (color) & 0xFF;
	res.a = 255;
	return (res);
}

static t_color	extract_four(int color)
{
	t_color	res;

	res.r = (color >> 8) & 0xFF;
	res.g = (color) & 0xFF;
	res.b = 0;
	res.a = 255;
	return (res);
}

static t_color	extract_two(int color)
{
	t_color	res;

	res.r = (color) & 0xFF;
	res.g = 0;
	res.b = 0;
	res.a = 255;
	return (res);
}

t_color	extract_rgba(int color, int len)
{
	t_color	res;

	res = (t_color){255, 255, 255, 255}; //TODO: Does it make sense?
	if (len == 8)
		res = extract_eight(color);
	else if (len == 6)
		res = extract_six(color);
	else if (len == 4)
		res = extract_four(color);
	else if (len == 2)
		res = extract_two(color);
	return (res);
}
