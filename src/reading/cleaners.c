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

void	clean_iso_matrix(t_iso_matrix *matrix)
{
	if (!matrix || !matrix->map)
		return ;
	clean_iso_map(&(matrix->map), matrix->height);
	matrix->map = NULL;
}

void	clean_px_matrix(t_px_matrix *matrix)
{
	int j;

	// TODO: so if map is null then we don't have height and width, right?
	if (!matrix || !matrix->map)
		return ;
	j = 0;
	while (j < matrix->height)
	{
		if (matrix->map[j])
			free(matrix->map[j]);
		j++;
	}
	free(matrix->map);
	matrix->map = NULL;
}

void	clean_arr(char **arr)
{
	int	len;
	int	i;

	len = array_len(arr);
	i = 0;
	while (i < len)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	clean_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}
