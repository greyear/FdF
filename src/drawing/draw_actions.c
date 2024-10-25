/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:03:15 by azinchen          #+#    #+#             */
/*   Updated: 2024/10/24 16:03:17 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"
#include <stdio.h>

void	default_picture(t_draw *pic)
{
	pic->zoom = 1; //Or should I put that zoom which came from width calculations?
	pic->move_x = 0;
	pic->move_y = 0;
	pic->flat = 1;
	pic->alpha = 0;
	pic->beta = 0;
	pic->gamma = 0;
	pic->parallel = 0;
}

void	refresh_picture(t_draw *pic)
{
	mlx_delete_image(pic->mlx, pic->image);
	draw_picture(pic->mlx, pic->read, pic);
}

void	delete_exit(t_draw *pic)
{
	mlx_delete_image(pic->mlx, pic->image);
	clean_read_map(&(pic->read));
	mlx_terminate(pic->mlx);
	exit(EXIT_SUCCESS);
}

void	track_keys(mlx_key_data_t keydata, void *param)
{
	t_draw	*pic;

	pic = (t_draw *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		delete_exit(pic);
	else if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN
		|| keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
		move(keydata, pic);
	else if (keydata.key == MLX_KEY_KP_1 || keydata.key == MLX_KEY_1
		|| keydata.key == MLX_KEY_KP_7 || keydata.key == MLX_KEY_7
		|| keydata.key == MLX_KEY_KP_2 || keydata.key == MLX_KEY_2
		|| keydata.key == MLX_KEY_KP_8 || keydata.key == MLX_KEY_8
		|| keydata.key == MLX_KEY_KP_3 || keydata.key == MLX_KEY_3
		|| keydata.key == MLX_KEY_KP_9 || keydata.key == MLX_KEY_9) //TODO: numlock?
		rotate(keydata, pic);
	else if (keydata.key == MLX_KEY_KP_0 || keydata.key == MLX_KEY_0)
	{
		default_picture(pic); //maybe not needed
		refresh_picture(pic);
	}
	else if (keydata.key == MLX_KEY_F || keydata.key == MLX_KEY_H)
		flatten(keydata, pic);
	else if (keydata.key == MLX_KEY_P || keydata.key == MLX_KEY_I)
		projection(keydata, pic);
}

void	track_scroll(double xdelta, double ydelta, void *param)
{
	t_draw	*pic;

	pic = (t_draw *)param;
	if (ydelta > 0 || ydelta < 0)
		zoom(ydelta, pic);
	(void)xdelta;
	refresh_picture(pic);
}
