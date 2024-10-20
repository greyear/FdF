
#include "../../include/fdf.h"

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

//void	track_scroll()
