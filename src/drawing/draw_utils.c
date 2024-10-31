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

	extremum.b_x = matrix.map[0][0].x;
	extremum.s_x = matrix.map[0][0].x;
	extremum.b_y = matrix.map[0][0].y;
	extremum.s_y = matrix.map[0][0].y;
	extremum.b_z = matrix.map[0][0].or_z;
	extremum.s_z = matrix.map[0][0].or_z;
	return (extremum);
}

t_extr	find_extremum(t_iso_mtx matrix)
{
	t_extr	ex;
	t_iso	m;
	int		i;
	int		j;

	ex = default_extremum(matrix);
	i = 0;
	while (i < matrix.width)
	{
		j = 0;
		while (j < matrix.height)
		{
			m = matrix.map[j][i];
			ex.b_x = (m.x > ex.b_x) * m.x + (ex.b_x >= m.x) * ex.b_x;
			ex.b_y = (m.y > ex.b_y) * m.y + (ex.b_y >= m.y) * ex.b_y;
			ex.b_z = (m.or_z > ex.b_z) * m.or_z + (ex.b_z >= m.or_z) * ex.b_z;
			ex.s_x = (m.x < ex.s_x) * m.x + (ex.s_x <= m.x) * ex.s_x;
			ex.s_y = (m.y < ex.s_y) * m.y + (ex.s_y <= m.y) * ex.s_y;
			ex.s_z = (m.or_z < ex.s_z) * m.or_z + (ex.s_z <= m.or_z) * ex.s_z;
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

	del_x = extremum.b_x - extremum.s_x;
	del_y = extremum.b_y - extremum.s_y;
	if (del_x == 0 && del_y == 0)
		zoom = 1.0;
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
