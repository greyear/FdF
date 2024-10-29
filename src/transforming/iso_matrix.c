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

static void	create_iso_mtx(t_iso_mtx *matrix, t_read *stack)
{
	int	j;

	matrix->map = (t_iso **)malloc(matrix->height * sizeof(t_iso *));
	if (!matrix->map)
	{
		clean_read_map(&stack);
		exit(EXIT_FAILURE);
	}
	j = 0;
	while (j < matrix->height)
	{
		matrix->map[j] = (t_iso *)malloc(matrix->width * sizeof(t_iso));
		if (!matrix->map[j])
		{
			clean_read_map(&stack);
			clean_iso_map(&(matrix->map), j);
			exit(EXIT_FAILURE);
		}
		j++;
	}
}

t_iso_mtx	fill_iso_mtx(double angle, t_draw *pic)
{
	t_read		*cur;
	int			i;
	int			j;
	t_iso_mtx	matrix;

	matrix.width = last_elem(pic->read)->x + 1;
	matrix.height = last_elem(pic->read)->y + 1;
	create_iso_mtx(&matrix, pic->read);
	cur = pic->read;
	j = 0;
	while (j < matrix.height)
	{
		i = 0;
		while (i < matrix.width)
		{
			matrix.map[j][i] = transform_point(*cur, angle, pic);
			cur = cur->next;
			i++;
		}
		j++;
	}
	return (matrix);
}
