/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:55:18 by azinchen          #+#    #+#             */
/*   Updated: 2024/10/29 18:55:20 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

int	draw_picture(t_draw *pic)
{
	t_iso_mtx	iso_matrix;
	t_px_mtx	pixel_matrix;

	iso_matrix = fill_iso_mtx(M_PI / 6, pic);
	pic->image = mlx_new_image(pic->mlx, pic->mlx->width, pic->mlx->height);
	if (!pic->image)
	{
		clean_read_map(&(pic->read));
		clean_iso_mtx(&iso_matrix);
		mlx_close_window(pic->mlx);
		ft_putstr_fd("Error creating MLX image\n", 2);
		exit(EXIT_FAILURE); //выйти?
	}
	pixel_matrix = fill_px_mtx(iso_matrix, pic);
	put_px_mtx(pic->image, pixel_matrix);
	if (mlx_image_to_window(pic->mlx, pic->image, 0, 0) == -1)
	{
		clean_read_map(&(pic->read));
		clean_iso_mtx(&iso_matrix);
		clean_px_mtx(&pixel_matrix);
		mlx_close_window(pic->mlx);
		ft_putstr_fd("Error displaying image in MLX window\n", 2);
		exit(EXIT_FAILURE); //выйти?
	}
	return (EXIT_SUCCESS);
}

void	pic_params(t_extr e, t_draw *pic)
{
	pic->mult = find_zoom(e, pic->image->width, pic->image->height) * pic->zoom;
	pic->of_x = (pic->image->width - pic->mult * (e.b_x - e.s_x)) / 2
		+ pic->mv_x;
	pic->of_y = (pic->image->height - pic->mult * (e.b_y - e.s_y)) / 2
		+ pic->mv_y;
}
