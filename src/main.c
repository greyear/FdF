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

/*
static void print_nodes(t_read *head) {
    t_read *current = head;
    while (current != NULL) {
        printf("Node:\n");
        printf("  x: %d\n", current->x);
        printf("  y: %d\n", current->y);
        printf("  z: %d\n", current->z);
        printf("  color: (%d, %d, %d)\n", current->color.r, current->color.g, current->color.b);
        current = current->next;
    }
}*/

int	main(int argc, char *argv[])
{
	t_read			*read;
	t_iso_matrix	iso_matrix;
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_px_matrix		pixel_matrix;

	//clock_t time_start= clock(); 

	if (argc != 2 || !argv[1])
		exit(EXIT_FAILURE); //TODO: do we need error msg here?
	read = read_map(argv[1]);
	//print_nodes(read);
	if (!read)
	{
		ft_printf("Invalid map\n");
		exit(EXIT_FAILURE);
	}
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
	pixel_matrix = to_px_matrix(image, iso_matrix);
	put_px_matrix(image, pixel_matrix);
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_loop(mlx);
	mlx_terminate(mlx);
	/*
	clock_t time_2 = clock() - time_start;
	printf("after all %f\n", (double)time_2 / CLOCKS_PER_SEC);
	*/
	return (EXIT_SUCCESS);
}
