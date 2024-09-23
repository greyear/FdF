

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

//Reading
t_read *read_map(char *file_name);

//Reading utils
t_read	*last_elem(t_read *stack);
int	add_back(t_read **stack, int x, int y, int z);

//Transforming
t_output    **transform_map(t_read *stack, double angle);


#endif
