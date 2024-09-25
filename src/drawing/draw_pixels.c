
#include "../../include/fdf.h"

/*
int pixel_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
} */

int	set_color(int z, int max_z, int min_z)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = 0 + (255 - 0) / (max_z - min_z) * (z - min_z);
	g = 128;
	b = 0 + (255 - 0) / (max_z - min_z) * (z - min_z);
	a = 255;

	return (r << 24 | g << 16 | b << 8 | a);
}


void put_matrix(mlx_image_t *image, t_matrix matrix)
{
	int				i;
	int				j;
	int				color;
	t_map_extremum	extremum;
	double			zoom_x;
	//double			zoom_y;

	extremum = find_extremum(matrix);
	// TODO: if not 0
	// TODO: change 1000!
	zoom_x = 900 / (extremum.max_x - extremum.min_x);
	//zoom_y = 900 / (extremum.max_y - extremum.min_y);
	i = 0;
	while (i < matrix.width)
	{
		j = 0;
		while (j < matrix.height)
		{

			color = set_color(matrix.map[j][i].z, extremum.max_z, extremum.min_z);
			mlx_put_pixel(image, (matrix.map[j][i].x - extremum.min_x) * zoom_x + 50, (matrix.map[j][i].y - extremum.min_y) * zoom_x + 50, color);
			j++;
		}
		i++;
	}
}
