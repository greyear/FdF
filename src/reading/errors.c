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
	ft_printf("Invalid arguments\n");
	exit(EXIT_FAILURE);
}

void	map_error(void)
{
	ft_printf("Invalid map\n");
	exit(EXIT_FAILURE);
}
