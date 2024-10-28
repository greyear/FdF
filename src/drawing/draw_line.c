/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:43:43 by azinchen          #+#    #+#             */
/*   Updated: 2024/10/28 19:43:47 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static t_line	line_params(t_px a, t_px b)
{
	t_line	line;

	line.del_x = abs(b.x - a.x);
	line.del_y = abs(b.y - a.y);
	if (a.x < b.x)
		line.sign_x = 1;
	else
		line.sign_x = -1;
	if (a.y < b.y)
		line.sign_y = 1;
	else
		line.sign_y = -1;
	line.error = line.del_x - line.del_y;
	return (line);
}

static void	put_first_point(mlx_image_t *image, t_px p)
{
	int	pixel_color;

	pixel_color = mix_rgba(p.color.r, p.color.g, p.color.b, p.color.a);
	if (is_inside(p.x, p.y, image->width, image->height))
		mlx_put_pixel(image, p.x, p.y, pixel_color);
}

static void	put_between_point(mlx_image_t *image, t_px	a_copy, t_px a, t_px b)
{
	t_color	color;
	int		pixel_color;

	color = color_between(a_copy, a, b);
	pixel_color = mix_rgba(color.r, color.g, color.b, color.a);
	if (is_inside(a.x, a.y, image->width, image->height))
		mlx_put_pixel(image, a.x, a.y, pixel_color);
}

void	draw_line(mlx_image_t *image, t_px a, t_px b)
{
	t_line	line;
	int		error2;
	t_px	a_copy;

	line = line_params(a, b);
	put_first_point(image, b);
	a_copy = a;
	while (a.x != b.x || a.y != b.y)
	{
		put_between_point(image, a_copy, a, b);
		error2 = line.error * 2;
		if (error2 > -line.del_y)
		{
			line.error -= line.del_y;
			a.x += line.sign_x;
		}
		if (error2 < line.del_x)
		{
			line.error += line.del_x;
			a.y += line.sign_y;
		}
	}
}
