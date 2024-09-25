

#include "../include/fdf.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	t_read	*read;
	t_matrix	matrix;

	mlx_t	*mlx;
    mlx_image_t	*image;

	if (argc != 2 || !argv[1])
		exit(1);
	read = read_map(argv[1]);
	matrix = transform_to_matrix(read, M_PI / 6);

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
	put_matrix(image, matrix);

	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
    {
        mlx_close_window(mlx);
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
