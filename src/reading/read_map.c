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
	int		fd;
	char	*line;
	char	**point_info;
	char	**separate;
	int		x;
	int		y;
	int		z;
	t_color	color;
	t_read	*first;
	t_read	*new;
	t_read	*last;
	char	*trimmed_line;
	int		exp_len;
	int		arr_len;

	fd = open_file(file_name);
	first = NULL;
	last = NULL;
	exp_len = -1;
	y = 0;
	while (1) //while line != NULL
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		trimmed_line = ft_strtrim(line, " \n\t\r\f\v");
		free(line);
		if (trimmed_line[0] == '\0')
		{
			free(trimmed_line);
			continue ;
		}
		point_info = ft_split(trimmed_line, ' ');
		free(trimmed_line);
		if (point_info == NULL)
		{
			clean_read_map(&first);
			clean_gnl(fd);
			ft_printf("Input data error\n");
			exit(EXIT_FAILURE);
		}
		arr_len = array_len(point_info);
		if (y == 0)
			exp_len = arr_len;
		else if (arr_len != exp_len)
		{
			clean_read_map(&first);
			clean_arr(point_info);
			clean_gnl(fd);
			ft_printf("Map is not rectangular\n");
			exit(EXIT_FAILURE);
		}
		x = 0;
		while (point_info[x] != NULL)
		{
			if (point_info[x][0] == '\0')
			{
				x++;
				continue ;
			}
			if (contains_comma(point_info[x]) == 1)
			{
				separate = ft_split(point_info[x], ',');
				if (array_len(separate) != 2 || height_check(separate[0]) || color_check(separate[1]))
				{
					ft_printf("Input data error\n");
					clean_read_map(&first);
					clean_arr(point_info);
					clean_arr(separate);
					clean_gnl(fd);
					exit(EXIT_FAILURE);
				}
				z = ft_atoi(separate[0]);
				color = extract_rgba(ft_atoi_color(separate[1]), ft_strlen(separate[1]) - 2);
				clean_arr(separate);
			}
			else
			{
				if (height_check(point_info[x]))
				{
					ft_printf("Input data error\n");
					clean_read_map(&first);
					clean_arr(point_info);
					clean_gnl(fd);
					exit(EXIT_FAILURE);
				}
				z = ft_atoi(point_info[x]);
				color = fake_color();
			}
			new = new_elem(x, y, z, color);
			if (new == NULL)
			{
				clean_read_map(&first);
				clean_arr(point_info);
				clean_gnl(fd);
				exit(EXIT_FAILURE);
			}
			last = add_to_back(&last, new);
			if (first == NULL)
				first = last;
			x++;
		}
		line = NULL;
		clean_arr(point_info);
		y++;
	}
	close(fd);
	return (first);
}
