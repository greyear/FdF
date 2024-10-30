/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:54:21 by azinchen          #+#    #+#             */
/*   Updated: 2024/10/09 16:41:08 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static int	open_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		error_opening();
	return (fd);
}

t_read	*read_map(char *file_name)
{
	t_start	start;

	start.fd = open_file(file_name);
	start.first = NULL;
	start.last = NULL;
	start.exp_len = -1;
	start.y = 0;
	while (1) //while line != NULL
	{
		start.line = get_next_line(start.fd);
		if (start.line == NULL)
			break ;
		start.point_info = separate_line(&start);
		if (start.point_info == NULL)
			continue ;
		start.arr_len = array_len(start.point_info);
		check_rectangular(start.y, start.arr_len, &start);
		parse_line(&start);
		start.y++;
	}
	close(start.fd);
	return (start.first);
}
