

#include "../../include/fdf.h"
#include "../../libft/include/get_next_line.h"
#include <stdio.h>


t_read	*last_elem(t_read *stack)
{
	t_read	*cur;

	if (!stack)
		return (NULL);
	cur = stack;
	while (cur->next)
		cur = cur->next;
	return (cur);
}

int	add_back(t_read **stack, int x, int y, int z)
{
	t_read	*last;
	t_read	*new;

	new = malloc(sizeof(t_read));
	if (!new)
		return (1);
	new->x = x;
	new->y = y;
	new->z = z;
	new->next = NULL;
	if (!*stack)
		*stack = new;
	else
	{
		last = last_elem(*stack);
		last->next = new;
	}
	return (0);
}

t_read *read_map(char *file_name)
{
	int			fd;
	char		*next_line;
	char		**split;
	int			x;
	int			y;
	int			z;
	t_read		*first;
	//t_read		*cur;
	
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		// TODO: clean?
		exit(1);
	first = NULL;
	y = 0;
	while (1)
	{
		next_line = get_next_line(fd);
		if (next_line == NULL)
			break ;
		split = ft_split(next_line, ' ');
		//checks
		x = 0;
		while (split[x] != NULL)
		{
			//checks for atoi
			z = ft_atoi(split[x]);
			if (add_back(&first, x, y, z) == 1)
				//clean
				exit(1);
			x++;
		}
		
		next_line = NULL;
		y++;
	}
	close(fd);
	return (first);
}

int main(int argc, char *argv[])
{
	int		i;
	t_read	*first;
	t_read	*cur;

	// TODO: checks for argv[1]? what should we do with argc?
	if (argc != 2)
		exit(1);
	first = read_map(argv[1]);
	i = 0;
	cur = first;
	while (cur != NULL)
	{
		printf("[%d]: %d, %d, %d", i, cur->x, cur->y, cur->z);
		i++;
		cur = cur->next;
	}
	return (0);
}