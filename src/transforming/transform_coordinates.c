/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_coordinates.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:55:31 by azinchen          #+#    #+#             */
/*   Updated: 2024/09/27 18:26:57 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static void	rotate_x(int *y, int *z, double alpha)
{
	int	previous_y;

	previous_y = *y;
	*y = previous_y * cos(alpha) + *z * sin(alpha);
	*z = -previous_y * sin(alpha) + *z * cos(alpha);
}

static void	rotate_y(int *x, int *z, double beta)
{
	int	previous_x;

	previous_x = *x;
	*x = previous_x * cos(beta) + *z * sin(beta);
	*z = -previous_x * sin(beta) + *z * cos(beta);
}

static void	rotate_z(int *x, int *y, double gamma)
{
	int	previous_x;
	int	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(gamma) - previous_y * sin(gamma);
	*y = previous_x * sin(gamma) + previous_y * cos(gamma);
}

static t_iso	transform_point(t_read p, double ang, t_draw *pic)
{
	t_iso	res;
	double	rot;

	rot = 2 * M_PI / 3;
	res.or_z = p.z;
	p.z /= pic->flat;
	rotate_x(&p.y, &p.z, pic->alpha);
	rotate_y(&p.x, &p.z, pic->beta);
	rotate_z(&p.x, &p.y, pic->gamma);
	res.x = p.x;
	res.y = p.y;
	(void)ang;
	if (pic->parallel == 0)
	{
		res.x = p.x * cos(ang) + p.y * cos(ang + rot) + p.z * cos(ang - rot);
		res.y = p.x * sin(ang) + p.y * sin(ang + rot) + p.z * sin(ang - rot);
		res.z = p.z;
	}
	res.color = p.color;
	return (res);
}

t_iso_mtx	to_iso_mtx(t_read *stack, double angle, t_draw *pic)
{
	t_read		*cur;
	int			i;
	int			j;
	int			width;
	int			height;
	t_iso		**map;
	t_iso_mtx	matrix;

	width = last_elem(stack)->x + 1;
	height = last_elem(stack)->y + 1;

	map = (t_iso **)malloc(height * sizeof(t_iso *));
	if (!map)
	{
		clean_read_map(&stack);
		exit(EXIT_FAILURE);
	}
	j = 0;
	while (j < height)
	{
		map[j] = (t_iso *)malloc(width * sizeof(t_iso));
		if (!map[j])
		{
			clean_read_map(&stack);
			clean_iso_map(&map, j);
			exit(EXIT_FAILURE);
		}
		j++;
	}
	cur = stack;
	j = 0;
	while (j < height)
	{
		i = 0;
		while (i < width)
		{
			map[j][i] = transform_point(*cur, angle, pic);
			cur = cur->next;
			i++;
		}
		j++;
	}
	matrix.map = map;
	matrix.width = width;
	matrix.height = height;
	return (matrix);
}
