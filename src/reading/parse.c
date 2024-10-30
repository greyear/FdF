/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:12:40 by azinchen          #+#    #+#             */
/*   Updated: 2024/10/30 20:12:42 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

char	**separate_line(t_start *start)
{
	char	*trimmed_line;
	char	**point_info;

	trimmed_line = ft_strtrim(start->line, " \n\t\r\f\v");
	free(start->line);
	if (trimmed_line[0] == '\0')
	{
		free(trimmed_line);
		return (NULL);
	}
	point_info = ft_split(trimmed_line, ' ');
	free(trimmed_line);
	if (point_info == NULL)
	{
		clean_read_map(&(start->first));
		clean_gnl(start->fd);
		ft_printf("Input data error\n");
		exit(EXIT_FAILURE);
	}
	return (point_info);
}

static int	parse_colored_point_data(char *point, t_start *start)
{
	char	**sep;

	sep = ft_split(point, ',');
	if (array_len(sep) != 2 || height_check(sep[0]) || color_check(sep[1]))
	{
		ft_printf("Input data error\n");
		clean_read_map(&(start->first));
		clean_arr(start->point_info);
		clean_arr(sep);
		clean_gnl(start->fd);
		exit(EXIT_FAILURE);
	}
	start->z = ft_atoi(sep[0]);
	start->color = extract_rgba(ft_atoi_color(sep[1]), ft_strlen(sep[1]) - 2);
	clean_arr(sep);
	return (0);
}

static int	parse_point_data(char *point, t_start *start)
{
	if (height_check(point))
	{
		ft_printf("Input data error\n");
		clean_read_map(&(start->first));
		clean_arr(start->point_info);
		clean_gnl(start->fd);
		exit(EXIT_FAILURE);
	}
	start->z = ft_atoi(point);
	start->color = fake_color();
	return (0);
}

static void	parse_and_add_point_data(t_start *start)
{
	t_read	*new;

	if (contains_comma(start->point_info[start->x]) == 1)
		parse_colored_point_data(start->point_info[start->x], start);
	else
		parse_point_data(start->point_info[start->x], start);
	new = new_elem(start->x, start->y, start->z, start->color);
	if (new == NULL)
	{
		clean_read_map(&(start->first));
		clean_arr(start->point_info);
		clean_gnl(start->fd);
		exit(EXIT_FAILURE);
	}
	start->last = add_to_back(&(start->last), new);
	if (start->first == NULL)
		start->first = start->last;
}

void	parse_line(t_start *start)
{
	start->x = 0;
	while (start->point_info[start->x] != NULL)
	{
		if (start->point_info[start->x][0] != '\0')
			parse_and_add_point_data(start);
		start->x++;
	}
	clean_arr(start->point_info);
}
