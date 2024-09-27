/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:54:21 by azinchen          #+#    #+#             */
/*   Updated: 2024/09/27 16:13:32 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

t_read	*read_map(char *file_name)
{
	int		fd;
	char	*next_line;
	char	**split;
	int		x;
	int		y;
	int		z;
	t_read	*first;
	
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		// TODO: clean?
		exit(1);
	first = NULL;
	y = 0;
	while (1)
	{
		next_line = get_next_line(fd);
		if (next_line == NULL)
			break ;
		split = ft_split(next_line, ' ');
		//checks
		x = 0;
		while (split[x] != NULL)
		{
			//checks for atoi
			z = ft_atoi(split[x]);
			if (add_back(&first, x, y, z) == 1)
				//clean
				exit(1);
			x++;
		}
		next_line = NULL;
		y++;
	}
	close(fd);
	return (first);
}
