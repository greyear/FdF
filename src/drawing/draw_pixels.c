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

t_px_mtx	to_px_mtx(mlx_image_t *image, t_iso_mtx iso_mtx, t_draw *pic)
{
	int				i;
	int				j;
	int				colorful;
	t_extr			extr;
	double			zoom;
	double			offset_x;
	double			offset_y;
	t_px_mtx		res;
	int				color;

	res.width = iso_mtx.width;
	res.height = iso_mtx.height;
	res.map = (t_px **)malloc(res.height * sizeof(t_px *));
	extr = find_extremum(iso_mtx);
	// TODO: if not 0
	zoom = find_zoom(extr, 1000, 1000) * pic->zoom; //hardcode
	offset_x = (1000 - zoom * (extr.b_x - extr.s_x)) / 2 + pic->move_x;
	offset_y = (1000 - zoom * (extr.b_y - extr.s_y)) / 2 + pic->move_y;
	colorful = is_colorful_input(iso_mtx);
	j = 0;
	while (j < res.height)
	{
		res.map[j] = (t_px *)malloc(res.width * sizeof(t_px));
		i = 0;
		while (i < res.width)
		{
			if (colorful == 1)
			{
				if (is_fake(iso_mtx.map[j][i].color) == 1)
					res.map[j][i].color = white_color();
				else
					res.map[j][i].color = iso_mtx.map[j][i].color;
			}
			else
				res.map[j][i].color = set_color_to_height(iso_mtx.map[j][i].or_z, extr.b_z, extr.s_z);
			color = mix_rgba(res.map[j][i].color.r, res.map[j][i].color.g, res.map[j][i].color.b, res.map[j][i].color.a);
			res.map[j][i].x = (iso_mtx.map[j][i].x - extr.s_x) * zoom + offset_x;
			res.map[j][i].y = (iso_mtx.map[j][i].y - extr.s_y) * zoom + offset_y;
			res.map[j][i].z = iso_mtx.map[j][i].z;
			if (is_inside(res.map[j][i].x, res.map[j][i].y, 1000, 1000)) //hardcode
				mlx_put_pixel(image, res.map[j][i].x, res.map[j][i].y, color);
			i++;
		}
		j++;
	}
	clean_iso_mtx(&iso_mtx);
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
	if (is_inside(b.x, b.y, image->width, image->height))
		mlx_put_pixel(image, b.x, b.y, pixel_color);
	a_copy = a;
	while (a.x != b.x || a.y != b.y)
	{
		color = color_between(a_copy, a, b);
		pixel_color = mix_rgba(color.r, color.g, color.b, color.a);
		if (is_inside(a.x, a.y, 1000, 1000)) //hardcode
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

void	put_px_mtx(mlx_image_t *image, t_px_mtx mtx)
{
	int	i;
	int	j;

	j = 0;
	while (j < mtx.height - 1)
	{
		i = 0;
		while (i < mtx.width - 1)
		{
			draw_line(image, mtx.map[j][i], mtx.map[j][i + 1]);
			draw_line(image, mtx.map[j][i], mtx.map[j + 1][i]);
			i++;
		}
		draw_line(image, mtx.map[j][i], mtx.map[j + 1][i]);
		j++;
	}
	j = mtx.height - 1;
	i = 0;
	while (i < mtx.width - 1)
	{
		draw_line(image, mtx.map[j][i], mtx.map[j][i + 1]);
		i++;
	}
	clean_px_mtx(&mtx);
}

/*
void	put_px_mtx(mlx_image_t *image, t_px_mtx mtx)
{
	int	i;
	int	j;

	j = 0;
	while (j < mtx.height - 1)
	{
		i = 0;
		while (i < mtx.width - 1)
		{
			draw_line(image, mtx.map[j][i], mtx.map[j][i + 1]);
			draw_line(image, mtx.map[j][i], mtx.map[j + 1][i]);
			i++;
		}
		j++;
	}
	j = mtx.height - 1;
	i = 0;
	while (i < mtx.width - 1)
	{
		draw_line(image, mtx.map[j][i], mtx.map[j][i + 1]);
		i++;
	}
	i = mtx.width - 1;
	j = 0;
	while (j < mtx.height - 1)
	{
		draw_line(image, mtx.map[j][i], mtx.map[j + 1][i]);
		j++;
	}
	clean_px_mtx(&mtx);
}*/
