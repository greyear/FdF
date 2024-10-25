/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:02:59 by azinchen          #+#    #+#             */
/*   Updated: 2024/10/24 16:03:01 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	move(mlx_key_data_t keydata, t_draw	*pic)
{
	if (keydata.key == MLX_KEY_UP) //do we need any limits set? maybe double limits?
		pic->move_y -= 5; //why are they reversed???
	else if (keydata.key == MLX_KEY_DOWN)
		pic->move_y += 5;
	else if (keydata.key == MLX_KEY_LEFT)
		pic->move_x -= 5;
	else if (keydata.key == MLX_KEY_RIGHT)
		pic->move_x += 5;
	refresh_picture(pic);
}

void	zoom(double ydelta, t_draw	*pic)
{
	if (ydelta > 0 && pic->zoom < 100)
		pic->zoom *= 1.02;
	else if (ydelta < 0 && pic->zoom > 0.001)
		pic->zoom /= 1.02;
	refresh_picture(pic);
}

void	rotate(mlx_key_data_t keydata, t_draw *pic)
{
	if (keydata.key == MLX_KEY_KP_1 || keydata.key == MLX_KEY_1)
		pic->alpha -= 0.05;
	else if(keydata.key == MLX_KEY_KP_7 || keydata.key == MLX_KEY_7)
		pic->alpha += 0.05;
	else if (keydata.key == MLX_KEY_KP_2 || keydata.key == MLX_KEY_2)
		pic->beta -= 0.05;
	else if (keydata.key == MLX_KEY_KP_8 || keydata.key == MLX_KEY_8)
		pic->beta += 0.05;
	else if (keydata.key == MLX_KEY_KP_3 || keydata.key == MLX_KEY_3)
		pic->gamma -= 0.05;
	else if (keydata.key == MLX_KEY_KP_9 || keydata.key == MLX_KEY_9)
	{
		pic->gamma += 0.05;
		printf("Gamma is %f\n", pic->gamma); //to check keyboard lag on home pc
	}
		
	refresh_picture(pic);
}

void	flatten(mlx_key_data_t keydata, t_draw *pic)
{
	if (keydata.key == MLX_KEY_F) //all keys seem to be pressed twice
	{
		pic->flat += 0.1;
		printf("Flat is %f\n", pic->flat);
	}
	else if (keydata.key == MLX_KEY_H)
		pic->flat -= 0.1;
	if (pic->flat < 0.5)
		pic->flat = 0.5;
	else if (pic->flat > 3.0)
		pic->flat = 3.0;
	refresh_picture(pic);
}

void	projection(mlx_key_data_t keydata, t_draw *pic)
{
	pic->alpha = 0;
	pic->beta = 0;
	pic->gamma = 0;
	if (keydata.key == MLX_KEY_P)
		pic->parallel = 1;
	if (keydata.key == MLX_KEY_I)
		pic->parallel = 0;
	refresh_picture(pic);
}
