

#ifndef FDF_H
# define FDF_H

# define _GNU_SOURCE

# include "../libft/include/libft.h"
# include "../libft/include/get_next_line.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdlib.h> //razobrat'sya s abs

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_color;

typedef struct s_read
{
	int				x;
	int				y;
	int				z;
	struct s_read	*next;
}	t_read;

typedef struct s_isometric
{
	double			x;
	double			y;
	int				z;
}	t_isometric;

typedef	struct s_iso_matrix
{
	t_isometric	**map;
	int			width;
	int			height;
}	t_iso_matrix;

typedef struct s_pixel
{
	int				x;
	int				y;
	int				z;
	t_color			color;
} t_pixel;

typedef	struct s_pixel_matrix
{
	t_pixel		**map;
	int			width;
	int			height;
}	t_pixel_matrix;

typedef struct s_extremum
{
	double	max_x;
	double	min_x;
	double	max_y;
	double	min_y;
	int		max_z;
	int		min_z;
}	t_extremum;

//Reading
t_read			*read_map(char *file_name);

//Reading utils
t_read			*last_elem(t_read *stack);
int				add_back(t_read **stack, int x, int y, int z);

//Transforming
t_iso_matrix		transform_to_matrix(t_read *stack, double angle);

//Drawing
int				pixel_color(int r, int g, int b, int a); //Ubrat'
void			put_matrix(mlx_image_t *image, t_iso_matrix matrix);
void	draw_line(mlx_image_t *image, t_pixel a, t_pixel b);

//Drawing utils
t_extremum	find_extremum(t_iso_matrix matrix);

#endif
