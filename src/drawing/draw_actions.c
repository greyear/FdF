
#include "../../include/fdf.h"
#include <stdio.h>

void	default_picture(t_draw *pic)
{
	pic->zoom = 1; //Or should I put that zoom which came from width calculations?
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

	pic = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		delete_exit(pic);
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
