

#include "../include/fdf.h"
#include <stdio.h>

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
		printf("[%d]: %d, %d, %d\n", i, cur->x, cur->y, cur->z);
		i++;
		cur = cur->next;
	}
	return (0);
}