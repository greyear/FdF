

#ifndef FDF_H
# define FDF_H

# define _GNU_SOURCE

# include "../libft/include/libft.h"
# include "../libft/include/get_next_line.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>

typedef struct s_read
{
	int				x;
	int				y;
	int				z;
	struct s_read	*next;
}	t_read;

typedef struct s_output
{
	double			x;
	double			y;
	int				z;
	int				color;
	//struct s_read	*next; Do we need it?
}	t_output;

typedef	struct s_matrix
{
	t_output	**map;
	int			width;
	int			height;
}	t_matrix;

typedef struct s_map_extremum
{
	double	max_x;
	double	min_x;
	double	max_y;
	double	min_y;
	int		max_z;
	int		min_z;
}	t_map_extremum;

/*
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_color; */

//Reading
t_read			*read_map(char *file_name);

//Reading utils
t_read			*last_elem(t_read *stack);
int				add_back(t_read **stack, int x, int y, int z);

//Transforming
t_matrix		transform_to_matrix(t_read *stack, double angle);

//Drawing
int				pixel_color(int r, int g, int b, int a); //Ubrat'
void			put_matrix(mlx_image_t *image, t_matrix matrix);

//Drawing utils
t_map_extremum	find_extremum(t_matrix matrix);

#endif
