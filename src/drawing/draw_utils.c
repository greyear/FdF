/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:53:31 by azinchen          #+#    #+#             */
/*   Updated: 2024/09/27 16:41:24 by azinchen         ###   ########.fr       */
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

