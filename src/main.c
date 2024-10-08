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
#include <stdio.h>

int	main(int argc, char *argv[])
{
	t_read			*read;
	t_iso_matrix	iso_matrix;
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_px_matrix		pixel_matrix;

	
	if (argc != 2 || !argv[1])
		exit(EXIT_FAILURE);
	read = read_map(argv[1]);

	// TODO: checks of read
	// TODO: if here function returned exit, will I have problems with memory?
	iso_matrix = to_iso_matrix(read, M_PI / 6);
	if (!(mlx = mlx_init(1000, 1000, "FDF", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 1000, 1000)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	pixel_matrix = to_px_matrix(iso_matrix);
	put_px_matrix(image, pixel_matrix);

	clock_t time_7 = clock() - time_start;
   	printf("after putting px matrix %f\n", (double)time_7 / CLOCKS_PER_SEC);

	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}

	clock_t time_8 = clock() - time_start;
   	printf("after drawing in window %f\n", (double)time_8 / CLOCKS_PER_SEC);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
