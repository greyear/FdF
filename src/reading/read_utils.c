/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:54:35 by azinchen          #+#    #+#             */
/*   Updated: 2024/10/01 19:38:45 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"
#include "../../libft/include/get_next_line.h"

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

int	add_back(t_read **stack, int x, int y, int z, t_color color)
{
	t_read	*last;
	t_read	*new;

	new = (t_read *)malloc(sizeof(t_read));
	if (!new)
		return (EXIT_FAILURE);
	new->x = x;
	new->y = y;
	new->z = z;
	new->color = color;
	new->next = NULL;
	if (!*stack)
		*stack = new;
	else
	{
		last = last_elem(*stack);
		last->next = new;
	}
	return (EXIT_SUCCESS);
}

int	contains_comma(char *str)
{
	char	c;
	int		i;

	c = ',';
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	array_len(char	**separate)
{
	int	len;

	len = 0;
	while (separate[len] != NULL) // TODO: \n?
		len++;
	return (len);
}
