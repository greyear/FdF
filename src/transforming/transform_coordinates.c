

#include "../../include/fdf.h"

static t_isometric    transform_point(t_read point, double angle)
{
	t_isometric    res;

	res.x = point.x * cos(angle) + point.y * cos(angle + 2 * M_PI / 3) + point.z * cos(angle - 2 * M_PI / 3);
	res.y = point.x * sin(angle) + point.y * sin(angle + 2 * M_PI / 3) + point.z * sin(angle - 2 * M_PI / 3);
	res.z = point.z;

	return (res);
}

t_iso_matrix    transform_to_matrix(t_read *stack, double angle)
{
	t_read  *cur;
	int     i;
	int     j;
	int     width;
	int     height;
	t_isometric    **map;
	t_iso_matrix    matrix;

	width = last_elem(stack)->x + 1;
	height = last_elem(stack)->y + 1;

	map = (t_isometric **)malloc(height * sizeof(t_isometric *));
	//what to return? what error msg?
	if (!map)
		exit(1);
	j = 0;
	while (j < height)
	{
		map[j] = (t_isometric *)malloc(width * sizeof(t_isometric));
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