/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:08:46 by azinchen          #+#    #+#             */
/*   Updated: 2024/10/25 20:08:47 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

int	color_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}

t_color	fake_color(void)
{
	t_color	res;

	res.r = -1;
	res.g = -1;
	res.b = -1;
	res.a = -1;
	return (res);
}

t_color	white_color(void)
{
	t_color	res;

	res.r = 255;
	res.g = 255;
	res.b = 255;
	res.a = 255;
	return (res);
}