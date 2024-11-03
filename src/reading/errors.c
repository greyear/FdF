/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:06:14 by azinchen          #+#    #+#             */
/*   Updated: 2024/10/28 20:06:16 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	args_error(void)
{
	ft_putstr_fd("Invalid arguments\n", 2);
	exit(EXIT_FAILURE);
}

void	map_error(void)
{
	ft_putstr_fd("Invalid map\n", 2);
	exit(EXIT_FAILURE);
}

void	error_opening(void)
{
	perror("Error opening file");
	exit(EXIT_FAILURE);
}

void	input_data_error(t_start *start)
{
	clean_read_map(&(start->first));
	clean_gnl(start->fd);
	close(start->fd);
	ft_putstr_fd("Input data error\n", 2);
	exit(EXIT_FAILURE);
}

void	mix_clean_exit(t_start *start)
{
	clean_read_map(&(start->first));
	clean_gnl(start->fd);
	close(start->fd);
	exit(EXIT_FAILURE);
}
