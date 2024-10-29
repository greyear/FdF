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

static void	create_px_mtx(t_px_mtx *px_mtx, t_iso_mtx *iso_mtx, t_draw *pic)
{
	int	j;

	px_mtx->map = (t_px **)malloc(px_mtx->height * sizeof(t_px *));
	if (!px_mtx->map)
	{
		//what to clean?
		clean_read_map(&(pic->read));
		clean_iso_mtx(iso_mtx);
		exit(EXIT_FAILURE);
	}
	j = 0;
	while (j < px_mtx->height)
	{
		px_mtx->map[j] = (t_px *)malloc(px_mtx->width * sizeof(t_px));
		if (!px_mtx->map[j])
		{
			//what to clean?
			clean_read_map(&(pic->read));
			clean_iso_mtx(iso_mtx);
			clean_px_map(&(px_mtx->map), j);
			exit(EXIT_FAILURE);
		}
		j++;
	}
}

static void	transform_iso(t_px *p, t_iso i, t_draw *pic)
{
	int		color;

	p->x = (i.x - pic->ext.s_x) * pic->mult + pic->of_x;
	p->y = (i.y - pic->ext.s_y) * pic->mult + pic->of_y;
	p->z = i.z;
	if (is_inside(p->x, p->y, pic->image->width, pic->image->height))
	{
		color = mix_rgba(p->color.r, p->color.g, p->color.b, p->color.a);
		mlx_put_pixel(pic->image, p->x, p->y, color);
	}
}

static void	fill_px_map(t_px_mtx *px, t_iso_mtx *iso, t_draw *pic)
{
	int		i;
	int		j;

	j = 0;
	while (j < px->height)
	{
		i = 0;
		while (i < px->width)
		{
			px->map[j][i].color = for_colorful_or_not(iso->map[j][i], pic);
			transform_iso(&(px->map[j][i]), iso->map[j][i], pic);
			i++;
		}
		j++;
	}
}

t_px_mtx	fill_px_mtx(t_iso_mtx iso_mtx, t_draw *pic)
{
	t_px_mtx	res;

	res.width = iso_mtx.width;
	res.height = iso_mtx.height;
	create_px_mtx(&res, &iso_mtx, pic);
	pic->colorful = is_colorful_input(iso_mtx);
	pic->ext = find_extremum(iso_mtx);
	// TODO: if not 0
	pic_params(pic->ext, pic);
	fill_px_map(&res, &iso_mtx, pic);
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
