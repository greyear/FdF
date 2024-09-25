
#include "../../include/fdf.h"

int	fake_color(void)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = 0;
	g = 128;
	b = 0;
	a = 255;

	return (r << 24 | g << 16 | b << 8 | a);
}

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

void	put_matrix(mlx_image_t *image, t_matrix matrix)
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
			//TODO: change to s_pixel
			mlx_put_pixel(image, (matrix.map[j][i].x - extremum.min_x) * zoom_x + 50, (matrix.map[j][i].y - extremum.min_y) * zoom_x + 50, color);
			j++;
		}
		i++;
	}
}

void	draw_line(mlx_image_t *image, t_pixel a, t_pixel b)
{
	int	del_x;
	int	del_y;
	int	sign_x;
	int	sign_y;
	int	error;
	int	error2;
	int	color;

	del_x = abs(b.x - a.x);
	del_y = abs(b.y - a.y);
	if (a.x < b.x)
		sign_x = 1;
	else
		sign_x = -1;
	if (a.y < b.y)
		sign_y = 1;
	else
		sign_y = -1;
	error = del_x - del_y;
	color = fake_color();
	mlx_put_pixel(image, b.x, b.y, color);
	while (a.x != b.x || a.y != b.y)
	{
		mlx_put_pixel(image, a.x, a.y, color);
		error2 = error * 2;
		if (error2 > -del_y)
		{
			error -= del_y;
			a.x += sign_x;
		}
		if (error2 < del_x)
		{
			error += del_x;
			a.y += sign_y;
		}
	}
}
