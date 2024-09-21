

#include "../../include/fdf.h"
#include "../../libft/include/get_next_line.h"

static t_read	*last_elem(t_read *stack)
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