/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:53:14 by azinchen          #+#    #+#             */
/*   Updated: 2024/10/09 18:32:43 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"
#include <stdio.h>

t_px_matrix	to_px_matrix(mlx_image_t *image, t_iso_matrix iso_matrix, t_draw *pic)
{
	int				i;
	int				j;
	int				colorful;
	t_extremum		extremum;
	double			zoom;
	double		offset_x;
	double		offset_y;
	t_px_matrix		res;
	int				color;

	res.width = iso_matrix.width;
	res.height = iso_matrix.height;
	res.map = (t_px **)malloc(res.height * sizeof(t_px *));
	extremum = find_extremum(iso_matrix);
	// TODO: if not 0
	// TODO: change 1000!
	zoom = find_zoom(extremum, 1000, 1000) * pic->zoom; //hardcode
	offset_x = (1000 - zoom * (extremum.max_x - extremum.min_x)) / 2;
	offset_y = (1000 - zoom * (extremum.max_y - extremum.min_y)) / 2;
	colorful = is_colorful_input(iso_matrix);
	j = 0;
	while (j < res.height)
	{
		res.map[j] = (t_px *)malloc(res.width * sizeof(t_px));
		i = 0;
		while (i < res.width)
		{
			if (colorful == 1)
			{
				if (is_fake(iso_matrix.map[j][i].color) == 1)
					res.map[j][i].color = white_color();
				else
					res.map[j][i].color = iso_matrix.map[j][i].color;
			}
			else
				res.map[j][i].color = set_color_to_height(iso_matrix.map[j][i].z, extremum.max_z, extremum.min_z);
			color = mix_rgba(res.map[j][i].color.r, res.map[j][i].color.g, res.map[j][i].color.b, res.map[j][i].color.a);
			res.map[j][i].x = (iso_matrix.map[j][i].x - extremum.min_x) * zoom + offset_x;
			res.map[j][i].y = (iso_matrix.map[j][i].y - extremum.min_y) * zoom + offset_y;
			res.map[j][i].z = iso_matrix.map[j][i].z;
			//TODO: check if inside
			mlx_put_pixel(image, res.map[j][i].x, res.map[j][i].y, color);
			i++;
		}
		j++;
	}
	clean_iso_matrix(&iso_matrix);
	return (res);
}

void	draw_line(mlx_image_t *image, t_px a, t_px b)
{
	int		del_x;
	int		del_y;
	int		sign_x;
	int		sign_y;
	int		error;
	int		error2;
	t_color	color;
	int		pixel_color;
	t_px	a_copy;

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
	pixel_color = mix_rgba(b.color.r, b.color.g, b.color.b, b.color.a);
	if (is_inside(b, image->width, image->height)) // hardcode
		mlx_put_pixel(image, b.x, b.y, pixel_color);
	a_copy = a;
	while (a.x != b.x || a.y != b.y)
	{
		color = color_between(a_copy, a, b);
		pixel_color = mix_rgba(color.r, color.g, color.b, color.a);
		if (is_inside(a, 1000, 1000)) //hardcode
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

void	put_px_matrix(mlx_image_t *image, t_px_matrix matrix)
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
	j = matrix.height - 1;
	i = 0;
	while (i < matrix.width - 1)
	{
		draw_line(image, matrix.map[j][i], matrix.map[j][i + 1]);
		i++;
	}
	i = matrix.width - 1;
	j = 0;
	while (j < matrix.height - 1)
	{
		draw_line(image, matrix.map[j][i], matrix.map[j + 1][i]);
		j++;
	}
	clean_px_matrix(&matrix);
}
