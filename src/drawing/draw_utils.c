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

static t_extr	default_extremum(t_iso_mtx matrix)
{
	t_extr	extremum;

	// TODO: check if map exists, if it has fields
	extremum.max_x = matrix.map[0][0].x;
	extremum.min_x = matrix.map[0][0].x;
	extremum.max_y = matrix.map[0][0].y;
	extremum.min_y = matrix.map[0][0].y;
	extremum.max_z = matrix.map[0][0].orig_z;
	extremum.min_z = matrix.map[0][0].orig_z;

	return (extremum);
}

t_extr	find_extremum(t_iso_mtx matrix)
{
	t_extr	ex;
	t_iso	m;
	int		i;
	int		j;

	// TODO: check if map exists, if it has fields
	ex = default_extremum(matrix);
	i = 0;
	while (i < matrix.width)
	{
		j = 0;
		while (j < matrix.height)
		{
			m = matrix.map[j][i]; //will change all z onto orig_z
			ex.max_x = (m.x > ex.max_x) * m.x + (ex.max_x >= m.x) * ex.max_x;
			ex.max_y = (m.y > ex.max_y) * m.y + (ex.max_y >= m.y) * ex.max_y;
			ex.max_z = (m.orig_z > ex.max_z) * m.orig_z + (ex.max_z >= m.orig_z) * ex.max_z;
			ex.min_x = (m.x < ex.min_x) * m.x + (ex.min_x <= m.x) * ex.min_x;
			ex.min_y = (m.y < ex.min_y) * m.y + (ex.min_y <= m.y) * ex.min_y;
			ex.min_z = (m.orig_z < ex.min_z) * m.orig_z + (ex.min_z <= m.orig_z) * ex.min_z;
			j++;
		}
		i++;
	}
	return (ex);
}

double	find_zoom(t_extr extremum, int width, int height)
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
	return (0);
}

int	is_inside(int x, int y, int limit_x, int limit_y)
{
	if ((x >= 0) && (y >= 0) && (x < limit_x) && (y < limit_y))
		return (1);
	return (0);
}
