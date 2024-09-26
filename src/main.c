

#include "../include/fdf.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	t_read	*read;
	t_iso_matrix	iso_matrix;

	mlx_t	*mlx;
    mlx_image_t	*image;

	/*t_pixel	a;
	t_pixel	b;*/

	if (argc != 2 || !argv[1])
		exit(1);
	read = read_map(argv[1]);
	iso_matrix = transform_to_matrix(read, M_PI / 6);

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
	//put_matrix(image, iso_matrix);
	
	/*a.x = 980;
	a.y = 930;
	a.color.r = 255;
	a.color.g = 128;
	a.color.b = 255;
	a.color.a = 255; //4286644223;
	b.x = 20;
	b.y = 20;
	b.color.r = 0;
	b.color.g = 128;
	b.color.b = 0;
	b.color.a = 255; //8388863;
	draw_line(image, a, b);*/

	t_pixel_matrix test = create_pixel_matrix(image, iso_matrix);
	/*if (test.map == NULL)
		return(EXIT_FAILURE);*/

	put_pixel_matrix(image, test);
	
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
