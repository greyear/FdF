
#include "../../include/fdf.h"

int pixel_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void put_matrix(mlx_image_t *image, t_matrix matrix)
{
	int				i;
	int				j;
	int				color;
	t_map_extremum	extremum;
	double			zoom_x;
	double			zoom_y;

	extremum = find_extremum(matrix);
	// TODO: if not 0
	// TODO: change 1000!
	zoom_x = 1000 / (extremum.max_x - extremum.min_x);
	zoom_y = 1000 / (extremum.max_y - extremum.min_y);
	i = 0;
	while (i < matrix.width)
	{
		j = 0;
		while (j < matrix.height)
		{
			color = pixel_color(0xFF, 0xFF, 0xFF, 0xFF);
			mlx_put_pixel(image, (matrix.map[j][i].x - extremum.min_x) * zoom_x, (matrix.map[j][i].y - extremum.min_y) * zoom_y, color);
			j++;
		}
		i++;
	}
}
