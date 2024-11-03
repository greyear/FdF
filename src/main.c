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

int	main(int argc, char *argv[])
{
	t_draw	pic;

	if (argc != 2 || !argv[1])
		args_error();
	name_check(argv[1]);
	pic.read = read_map(argv[1]);
	if (!pic.read)
		map_error();
	pic.mlx = mlx_init(1000, 1000, "FDF", true);
	if (!pic.mlx)
	{
		clean_read_map(&(pic.read));
		ft_putstr_fd("Error initializing MLX\n", 2);
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
