
#include "../../include/fdf.h"
#include <stdio.h>

void	default_picture(t_draw *pic)
{
	pic->zoom = 1; //Or should I put that zoom which came from width calculations?
	pic->move_x = 0;
	pic->move_y = 0;
	pic->flat_z = 0;
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
	if (keydata.key == MLX_KEY_UP) //do we need any limits set? maybe double limits?
		pic->move_y -= 5; //why are they reversed???
	if (keydata.key == MLX_KEY_DOWN)
		pic->move_y += 5;
	if (keydata.key == MLX_KEY_LEFT)
		pic->move_x -= 5;
	if (keydata.key == MLX_KEY_RIGHT)
		pic->move_x += 5;
	if (keydata.key == MLX_KEY_F)
		pic->flat_z -= 10;
	if (keydata.key == MLX_KEY_H)
		pic->flat_z += 10;
	refresh_picture(pic);
}

void	track_scroll(double xdelta, double ydelta, void *param)
{
	t_draw	*pic;

	pic = (t_draw *)param;
	if (ydelta > 0 && pic->zoom < 100)
		pic->zoom *= 1.02;
	else if (ydelta < 0 && pic->zoom > 0.001)
		pic->zoom /= 1.02;
	(void)xdelta;
	refresh_picture(pic);
}
