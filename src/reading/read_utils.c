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

int	add_back(t_read **stack, int x, int y, int z)
{
	t_read	*last;
	t_read	*new;

	new = malloc(sizeof(t_read));
	if (!new)
		return (EXIT_FAILURE);
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

static int	conv_hexa_digit(char c)
{
	
}

int	htoi_(char *str)
{
	int	res;
	int	sign;


}
