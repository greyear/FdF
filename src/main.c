

#include "../include/fdf.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	//t_read	*read;
	//t_iso_matrix	matrix;

	mlx_t	*mlx;
    mlx_image_t	*image;

	t_pixel	a;
	t_pixel	b;

	if (argc != 2 || !argv[1])
		exit(1);
	//read = read_map(argv[1]);
	//matrix = transform_to_matrix(read, M_PI / 6);

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
	//put_matrix(image, matrix);
	a.x = 980;
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
	draw_line(image, a, b);

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

/*
#define WIDTH 512
#define HEIGHT 512

static mlx_image_t* image;

// -----------------------------------------------------------------------------

int ft_pixel(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	(void)param;
	for (int i = 0; i < (int)image->width; ++i)
	{
		for (int y = 0; y < (int)image->height; ++y)
		{
			//int color = ft_pixel(0, 128, 0, 255);
			mlx_put_pixel(image, i, y, -7188091);
		}
	}
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

// -----------------------------------------------------------------------------

int32_t main(void)
{
	mlx_t* mlx;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 128, 128)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
*/