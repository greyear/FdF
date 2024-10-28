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
