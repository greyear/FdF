

#include "../include/fdf.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	t_read	*read;
	t_output	**matrix;
	//t_read	*cur;
	int	width;
    int	height;
	int	i;
	int	j;
	int	num;

	// TODO: checks for argv[1]? what should we do with argc?
	if (argc != 2)
		exit(1);
	read = read_map(argv[1]);
	width = last_elem(read)->x + 1;
    height = last_elem(read)->y + 1;
	matrix = transform_map(read, M_PI / 6);
	num = 0;
	j = 0;
    while (j < height)
    {
        i = 0;
        while (i < width)
        {
            printf("[%d]: %f, %f\n", num, matrix[j][i].x, matrix[j][i].y);
            i++;
			num++;
        }
        j++;
    }
	/*i = 0;
	cur = first;
	while (cur != NULL)
	{
		printf("[%d]: %d, %d, %d\n", i, cur->x, cur->y, cur->z);
		i++;
		cur = cur->next;
	}*/
	return (0);
}
