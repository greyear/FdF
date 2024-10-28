/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:52:38 by azinchen          #+#    #+#             */
/*   Updated: 2024/10/09 18:31:16 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	draw_picture(t_draw *pic)
{
	t_iso_mtx	iso_matrix;
	t_px_mtx	pixel_matrix;
	mlx_image_t	*image;

	iso_matrix = to_iso_mtx(pic->read, M_PI / 6, pic);
	image = mlx_new_image(pic->mlx, pic->mlx->width, pic->mlx->height);
	if (!image)
	{
		//clean all
		mlx_close_window(pic->mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	pixel_matrix = to_px_mtx(image, iso_matrix, pic);
	put_px_mtx(image, pixel_matrix);
	if (mlx_image_to_window(pic->mlx, image, 0, 0) == -1)
	{
		//clean all
		mlx_close_window(pic->mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	pic->image = image;
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_draw	pic;

	if (argc != 2 || !argv[1])
		args_error();
	pic.read = read_map(argv[1]);
	if (!pic.read)
		map_error();
	pic.mlx = mlx_init(1000, 1000, "FDF", true);
	if (!pic.mlx)
	{
		//clean all
		clean_read_map(&(pic.read));
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	default_picture(&pic);
	draw_picture(&pic);
	mlx_key_hook(pic.mlx, track_keys, &pic);
	mlx_scroll_hook(pic.mlx, track_scroll, &pic);
	mlx_loop(pic.mlx);
	clean_read_map(&(pic.read));
	mlx_terminate(pic.mlx);
	return (EXIT_SUCCESS);
}
