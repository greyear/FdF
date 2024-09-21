

#ifndef FDF_H
# define FDF_H

# include "../libft/include/libft.h"
# include "../libft/include/get_next_line.h"
# include "../MLX42/include/MLX42/MLX42.h"
//What about 2nd header?

typedef struct s_read
{
	int				x;
	int				y;
	int				z;
	struct s_read	*next;
}	t_read;
//double?

//Reading
t_read *read_map(char *file_name);

//Utils
int	add_back(t_read **stack, int x, int y, int z);



#endif