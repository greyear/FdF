

#ifndef FDF_H
# define FDF_H

#define _GNU_SOURCE
//# define __USE_XOPEN

# include "../libft/include/libft.h"
# include "../libft/include/get_next_line.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
//What about 2nd header?

typedef struct s_read
{
	int				x;
	int				y;
	int				z;
	struct s_read	*next;
}	t_read;
//double?

typedef struct s_output
{
	double			x;
	double			y;
	int32_t			color;
	struct s_read	*next;
}	t_output;

typedef	struct s_matrix
{
	t_output	**map;
	int			width;
	int			height;
}	t_matrix;

typedef struct s_map_extremum
{
	double	max_y;
	double	min_y;
	double	max_x;
	double	min_x;
}	t_map_extremum;

//Reading
t_read *read_map(char *file_name);

//Reading utils
t_read	*last_elem(t_read *stack);
int	add_back(t_read **stack, int x, int y, int z);

//Transforming
t_matrix	transform_to_matrix(t_read *stack, double angle);

//Drawing
int		pixel_color(int r, int g, int b, int a); //Ubrat'
void	put_matrix(mlx_image_t *image, t_matrix matrix);

//Drawing utils
t_map_extremum find_extremum(t_matrix matrix);

#endif