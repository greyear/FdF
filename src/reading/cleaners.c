/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:42:01 by azinchen          #+#    #+#             */
/*   Updated: 2024/09/30 18:25:42 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	clean_read_map(t_read **stack)
{
	t_read	*next;
	t_read	*cur;

	if (!stack || !*stack)
		return ;
	cur = *stack;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	*stack = NULL;
}

