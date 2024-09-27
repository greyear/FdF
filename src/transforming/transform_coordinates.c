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

static t_iso	transform_point(t_read p, double ang)
{
	t_iso	res;
	double		rot;

	rot = 2 * M_PI / 3;
	res.x = p.x * cos(ang) + p.y * cos(ang + rot) + p.z * cos(ang - rot);
	res.y = p.x * sin(ang) + p.y * sin(ang + rot) + p.z * sin(ang - rot);
	res.z = p.z;

	return (res);
}

t_iso_matrix	to_iso_matrix(t_read *stack, double angle)
{
	t_read			*cur;
	int				i;
	int				j;
	int				width;
	int				height;
	t_iso		**map;
	t_iso_matrix	matrix;

	width = last_elem(stack)->x + 1;
	height = last_elem(stack)->y + 1;

	map = (t_iso **)malloc(height * sizeof(t_iso *));
	//what to return? what error msg?
	if (!map)
		exit(1);
	j = 0;
	while (j < height)
	{
		map[j] = (t_iso *)malloc(width * sizeof(t_iso));
		//what to return? what error msg?
		if (!map[j])
			exit(1);
		j++;
	}
	cur = stack;
	j = 0;
	while (j < height)
	{
		i = 0;
		while (i < width)
		{
			map[j][i] = transform_point(*cur, angle);
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
