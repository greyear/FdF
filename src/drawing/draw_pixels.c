
#include "../../include/fdf.h"
#include <stdio.h>

int	mix_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

t_color	set_color(int z, int max_z, int min_z)
{
	t_color	res;

	res.r = 0 + (255 - 0) / (max_z - min_z) * (z - min_z);
	res.g = 128;
	res.b = 0 + (255 - 0) / (max_z - min_z) * (z - min_z);
	res.a = 255;

	return (res);
}

t_color	intermediate_color(t_pixel start, t_pixel cur, t_pixel end)
{
	int	del_small;
	int	del_big;
	t_color	res;

	del_small = abs(cur.x - start.x) + abs(cur.y - start.y);
	del_big = abs(end.x - start.x) + abs(end.y - start.y);
	res.r = start.color.r + ((end.color.r - start.color.r) * del_small) / del_big;
	res.g = start.color.g + ((end.color.g - start.color.g) * del_small) / del_big;
	res.b = start.color.b + ((end.color.b - start.color.b) * del_small) / del_big;
	res.a = start.color.a + ((end.color.a - start.color.a) * del_small) / del_big;
	return (res);
}

void	draw_line(mlx_image_t *image, t_pixel a, t_pixel b)
{
	int	del_x;
	int	del_y;
	int	sign_x;
	int	sign_y;
	int	error;
	int	error2;
	t_color	color;
	int		pixel_color;
	t_pixel a_copy;

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

	pixel_color = mix_color(b.color.r, b.color.g, b.color.b, b.color.a);
	mlx_put_pixel(image, b.x, b.y, pixel_color);
	a_copy = a;
	while (a.x != b.x || a.y != b.y)
	{
		color = intermediate_color(a_copy, a, b);
		pixel_color = mix_color(color.r, color.g, color.b, color.a);
		mlx_put_pixel(image, a.x, a.y, pixel_color);
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

/*
void	put_matrix(mlx_image_t *image, t_iso_matrix matrix)
{
	int				i;
	int				j;
	int				color;
	t_extremum	extremum;
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
}*/

t_pixel_matrix	create_pixel_matrix(mlx_image_t *image, t_iso_matrix iso_matrix)
{
	int				i;
	int				j;
	int				color;
	t_extremum	extremum;
	double			zoom_x;
	//double			zoom_y;
	t_pixel_matrix		res;

	res.width = iso_matrix.width;
	res.height = iso_matrix.height;
	res.map = (t_pixel **)malloc(res.height * sizeof(t_pixel *));

	extremum = find_extremum(iso_matrix);
	// TODO: if not 0
	// TODO: change 1000!
	zoom_x = 900 / (extremum.max_x - extremum.min_x);
	//zoom_y = 900 / (extremum.max_y - extremum.min_y);
	j = 0;
	while (j < res.height)
	{
		res.map[j] = (t_pixel *)malloc(res.width * sizeof(t_pixel));
		i = 0;
		while (i < res.width)
		{
			res.map[j][i].color = set_color(iso_matrix.map[j][i].z, extremum.max_z, extremum.min_z);
			color = mix_color(res.map[j][i].color.r, res.map[j][i].color.g, res.map[j][i].color.b, res.map[j][i].color.a);
			res.map[j][i].x = (iso_matrix.map[j][i].x - extremum.min_x) * zoom_x + 50;
			res.map[j][i].y = (iso_matrix.map[j][i].y - extremum.min_y) * zoom_x + 50;
			res.map[j][i].z = iso_matrix.map[j][i].z; //TODO: check if it's needed
			//TODO: change to s_pixel
			mlx_put_pixel(image, res.map[j][i].x, res.map[j][i].y, color);
			i++;
		}
		j++;
	}
	return (res);
}

void	put_pixel_matrix(mlx_image_t *image, t_pixel_matrix matrix)
{
	int	i;
	int	j;

	j = 0;
	while (j < matrix.height - 1)
	{
		i = 0;
		while (i < matrix.width - 1)
		{
			draw_line(image, matrix.map[j][i], matrix.map[j][i + 1]);
			draw_line(image, matrix.map[j][i], matrix.map[j + 1][i]);
			i++;
		}
		j++;
	}
}
