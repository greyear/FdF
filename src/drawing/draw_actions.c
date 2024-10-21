
#include "../../include/fdf.h"
#include <stdio.h>

void	default_picture(t_draw *pic)
{
	pic->zoom = 1; //Or should I put that zoom which came from width calculations?
}

void	refresh_picture(mlx_t *mlx, mlx_image_t *image, t_draw *pic)
{
	mlx_delete_image(mlx, image);
	draw_picture(mlx, pic->read, pic);
}

void	delete_exit(mlx_t *mlx, mlx_image_t *image)
{
	mlx_delete_image(mlx, image);
	mlx_terminate(mlx);
	exit(EXIT_SUCCESS);
}

void	track_keys(mlx_key_data_t keydata, void *param)
{
	t_draw	*pic;

	pic = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		delete_exit(pic->mlx, pic->image);
}

void	track_scroll(double xdelta, double ydelta, void *param)
{
	t_draw	*pic;

	printf("Here");
	pic = (t_draw *)param;
	if (ydelta > 0)
		pic->zoom *= 1.02;
	else if (ydelta < 0)
		pic->zoom /= 1.02; //TODO: why can't I divide? Or can I hah?
	(void)xdelta;
	refresh_picture(pic->mlx, pic->image, pic);
}

//void	track_scroll()
