
#include "../../include/fdf.h"

t_map_extremum find_extremum(t_matrix matrix)
{
	t_map_extremum	extremum;
	int				i;
	int				j;

	// TODO: check if map exists, if it has fields
	extremum.max_y = matrix.map[0][0].y;
	extremum.min_y = matrix.map[0][0].y;
	extremum.max_x = matrix.map[0][0].x;
	extremum.min_x = matrix.map[0][0].x;
	i = 0;
	while (i < matrix.width)
	{
		j = 0;
		while (j < matrix.height)
		{
			if (matrix.map[j][i].y > extremum.max_y)
				extremum.max_y = matrix.map[j][i].y;
			if (matrix.map[j][i].y < extremum.min_y)
				extremum.min_y = matrix.map[j][i].y;
			if (matrix.map[j][i].x > extremum.max_x)
				extremum.max_x = matrix.map[j][i].x;
			if (matrix.map[j][i].x < extremum.min_x)
				extremum.min_x = matrix.map[j][i].x;
			j++;
		}
		i++;
	}
	return (extremum);
}

