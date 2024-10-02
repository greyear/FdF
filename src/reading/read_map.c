/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:54:21 by azinchen          #+#    #+#             */
/*   Updated: 2024/10/02 14:48:36 by azinchen         ###   ########.fr       */
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
	{
		// TODO: clean?
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
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
			/*
			   1) check for ","
			   2) split to 2 values
			   3) check and convert 1st
			   4) check and convert 2nd 


			*/
			z = ft_atoi(split[x]);
			if (add_back(&first, x, y, z) == 1)
			{
				clean_read_map(&first);
				exit(EXIT_FAILURE);
			}	
			x++;
		}
		next_line = NULL;
		y++;
	}
	close(fd);
	return (first);
}
