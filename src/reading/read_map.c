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
#include <stdio.h> // TODO: delete

t_read	*read_map(char *file_name)
{
	int		fd;
	char	*line;
	char	**point_info;
	char	**separate;
	int		x;
	int		y;
	int		z;
	t_color	color;
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
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		point_info = ft_split(line, ' ');
		//checks for point_info
		free(line);
		//printf("x:%d", x);
		x = 0;
		while (point_info[x] != NULL)
		{
			if (contains_comma(point_info[x]) == 1)
			{
				separate = ft_split(point_info[x], ',');
				if (array_len(separate) != 2)
					{
						perror("Input data error: array_len");
						exit(EXIT_FAILURE);
					}
				if (height_check(separate[0]) == 1)
					{
						perror("Input data error: height check");
						exit(EXIT_FAILURE);
					}
				if (color_check(separate[1]) == 1)
					{
						perror("Input data error: color check");
						exit(EXIT_FAILURE);
					}
				z = ft_atoi(separate[0]);
				color = extract_rgba(ft_atoi_color(separate[1]), ft_strlen(separate[1]) - 2);
				clean_arr(separate);
			}
			else
			{
				z = ft_atoi(point_info[x]);
				color = fake_color();
			}
			if (add_back(&first, x, y, z, color) == 1)
			{
				clean_read_map(&first);
				exit(EXIT_FAILURE);
			}
			x++;
		}
		line = NULL; //why do I need it?
		clean_arr(point_info);
		y++;
	}
	//printf("y:%d", y);
	close(fd);
	return (first);
}
