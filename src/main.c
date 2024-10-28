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

int	draw_picture(mlx_t *mlx, t_read *read, t_draw *pic)
{
	t_iso_mtx	iso_matrix;
	t_px_mtx	pixel_matrix;
	mlx_image_t	*image;

	iso_matrix = to_iso_mtx(read, M_PI / 6, pic);
	//if (!(image = mlx_new_image(mlx, 1000, 1000)))
	if (!(image = mlx_new_image(mlx, mlx->width, mlx->height)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	pixel_matrix = to_px_mtx(image, iso_matrix, pic);
	put_px_mtx(image, pixel_matrix);
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	pic->mlx = mlx;
	pic->image = image;
	pic->read = read;
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_read	*read;
	mlx_t	*mlx;
	t_draw	pic;

	if (argc != 2 || !argv[1])
		args_error();
	read = read_map(argv[1]);
	if (!read)
		map_error();
	if (!(mlx = mlx_init(1000, 1000, "FDF", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	default_picture(&pic);
	draw_picture(mlx, read, &pic);
	mlx_key_hook(mlx, track_keys, &pic);
	mlx_scroll_hook(mlx, track_scroll, &pic);
	mlx_loop(mlx);
	clean_read_map(&read);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
