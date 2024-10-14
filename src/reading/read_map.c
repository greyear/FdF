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
	t_read	*last;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	first = NULL;
	last = NULL;
	y = 0;
	while (1) //while line != NULL
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (is_nl(line)) //I added this to return error msg in maps with nl, but now I have a leak
		{
			free(line);
			continue ;
		}
		point_info = ft_split(line, ' '); //TODO: what about other types of spaces?
		if (point_info == NULL)
		{
			free(line);
			clean_read_map(&first); //??
			ft_printf("Input data error\n"); //TODO: do we need to clean first and separate?
			exit(EXIT_FAILURE);
		}
		//checks for point_info
		free(line);
		//printf("x:%d", x);
		x = 0;
		while (point_info[x] != NULL)
		{
			//printf("[%d] '%s' - x, point_info[x]\n", x, point_info[x]);
			if (contains_comma(point_info[x]) == 1)
			{
				separate = ft_split(point_info[x], ',');
				if (array_len(separate) != 2 || height_check(separate[0]) || color_check(separate[1]))
				{
					ft_printf("Input data error\n"); //TODO: do we need to clean first and separate?
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
			last = add_to_last(&last, x, y, z, color);
			if (last == NULL)
			{
				clean_read_map(&first);
				exit(EXIT_FAILURE);
			}
			if (first == NULL)
				first = last;
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
