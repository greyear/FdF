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

t_read	*new_elem(int x, int y, int z, t_color color)
{
	t_read	*new;

	new = (t_read *)malloc(sizeof(t_read));
	if (!new)
		return (NULL);
	new->x = x;
	new->y = y;
	new->z = z;
	new->color = color;
	new->next = NULL;
	return (new);
}

t_read	*add_to_back(t_read **old_last, t_read *new_last)
{
	if (*old_last)
		(*old_last)->next = new_last;
	return (new_last);
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
	while (separate[len] != NULL)
		len++;
	return (len);
}
