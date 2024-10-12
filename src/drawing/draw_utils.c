/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:53:31 by azinchen          #+#    #+#             */
/*   Updated: 2024/10/09 18:04:00 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

t_extremum find_extremum(t_iso_matrix matrix)
{
	t_extremum		extremum;
	int				i;
	int				j;

	// TODO: check if map exists, if it has fields
	extremum.max_x = matrix.map[0][0].x;
	extremum.min_x = matrix.map[0][0].x;
	extremum.max_y = matrix.map[0][0].y;
	extremum.min_y = matrix.map[0][0].y;
	extremum.max_z = matrix.map[0][0].z;
	extremum.min_z = matrix.map[0][0].z;
	i = 0;
	while (i < matrix.width)
	{
		j = 0;
		while (j < matrix.height)
		{
			if (matrix.map[j][i].x > extremum.max_x)
				extremum.max_x = matrix.map[j][i].x;
			if (matrix.map[j][i].x < extremum.min_x)
				extremum.min_x = matrix.map[j][i].x;
			if (matrix.map[j][i].y > extremum.max_y)
				extremum.max_y = matrix.map[j][i].y;
			if (matrix.map[j][i].y < extremum.min_y)
				extremum.min_y = matrix.map[j][i].y;
			if (matrix.map[j][i].z > extremum.max_z)
				extremum.max_z = matrix.map[j][i].z;
			if (matrix.map[j][i].z < extremum.min_z)
				extremum.min_z = matrix.map[j][i].z;
			j++;
		}
		i++;
	}
	return (extremum);
}

double	find_zoom(t_extremum extremum, int width, int height)
{
	double		zoom;
	double		del_x;
	double		del_y;

	del_x = extremum.max_x - extremum.min_x;
	del_y = extremum.max_y - extremum.min_y;
	if (del_x == 0 && del_y == 0)
		zoom = 1.0; //TODO: is this right?
	else if (del_x == 0)
		zoom = height / del_y * 0.9;
	else if (del_y == 0)
		zoom = width / del_x * 0.9;
	else
	{
		if (width / del_x < height / del_y)
			zoom = width / del_x * 0.9;
		else
			zoom = height / del_y * 0.9;
	}
	return (zoom);
}

int	is_fake(t_color c)
{
	if (c.r == -1 && c.g == -1 && c.b == -1 && c.a == -1)
		return (1);
	return(0);
}

int	is_colorful_input(t_iso_matrix matrix)
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

int	is_inside(t_px a, int limit_x, int limit_y)
{
	if (a.x <= limit_x && a.y <= limit_y) //TODO: or <?
		return (1);
	return (0);
}
