

#include "../../include/fdf.h"

static t_output    transform_point(t_read point, double angle)
{
    t_output    res;

    res.x = point.x * cos(angle) + point.y * cos(angle + 2 * M_PI / 3) + point.z * cos(angle - 2 * M_PI / 3);
    res.y = point.x * sin(angle) + point.y * sin(angle + 2 * M_PI / 3) + point.z * sin(angle - 2 * M_PI / 3);

    return (res);
}

t_output    **transform_map(t_read *stack, double angle)
{
    t_read  *cur;
    int     i;
    int     j;
    int     width;
    int     height;
    t_output    **map;

    width = last_elem(stack)->x + 1;
    height = last_elem(stack)->y + 1;

    map = (t_output **)malloc(height * sizeof(t_output *));
    //what to return? what error msg?
    if (!map)
        return (NULL);
    j = 0;
    while (j < height)
    {
        map[j] = (t_output *)malloc(width * sizeof(t_output));
        //what to return? what error msg?
        if (!map[j])
            return (NULL);
        j++;
    }
    cur = stack;
    j = 0;
    while (j < height)
    {
        i = 0;
        while (i < width)
        {
            map[j][i] = transform_point(*cur, angle);
            cur = cur->next;
            i++;
        }
        j++;
    }
    return (map);
}