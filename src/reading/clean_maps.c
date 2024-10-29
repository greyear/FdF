/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_maps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:26:02 by azinchen          #+#    #+#             */
/*   Updated: 2024/10/29 14:26:04 by azinchen         ###   ########.fr       */
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

void	clean_iso_map(t_iso ***map, int height)
{
	int	j;

	if (!map || !(*map))
		return ;
	j = 0;
	while (j < height && (*map)[j] != NULL)
	{
		free((*map)[j]);
		j++;
	}
	free(*map);
}

void	clean_iso_mtx(t_iso_mtx *matrix)
{
	if (!matrix || !matrix->map)
		return ;
	clean_iso_map(&(matrix->map), matrix->height);
	matrix->map = NULL;
}

void	clean_px_map(t_px ***map, int height)
{
	int	j;

	if (!map || !(*map))
		return ;
	j = 0;
	while (j < height && (*map)[j] != NULL)
	{
		free((*map)[j]);
		j++;
	}
	free(*map);
}

void	clean_px_mtx(t_px_mtx *matrix)
{
	if (!matrix || !matrix->map)
		return ;
	clean_px_map(&(matrix->map), matrix->height);
	matrix->map = NULL;
}
