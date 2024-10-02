/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:25:22 by azinchen          #+#    #+#             */
/*   Updated: 2024/10/02 19:41:46 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"
#include <stdio.h>

int	contains_comma(char *str)
{
	char	c;
	int		i;

	c = ',';
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	height_check(char *str)
{
	int	i;
	int	value;

	if (!str)
		return (EXIT_FAILURE);
	if (!ft_isdigit(str[0]) && !ft_issign(str[0]))
			return (EXIT_FAILURE);
	// case with only sign without digits
	if (ft_issign(str[0]) && (!ft_isdigit(str[1]) || str[1] == '\0'))
		return (EXIT_FAILURE);
	i = 1;
	while (str[i] != '\0') //TODO: can "\n" be here at some point?
	{
		if (!ft_isdigit(str[i]))
			return (EXIT_FAILURE);
		i++;
	}
	value = ft_atoi(str);
	if (value < -1000000 || value > 1000000) //TODO: hardcode?
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	color_check(char *str)
{
	int		i;
	char	c;

	if (!str)
		return (EXIT_FAILURE);
	if (!(ft_strlen(str) == 8 || ft_strlen(str) == 10))
		return (EXIT_FAILURE);
	if (str[0] != '0' || ft_tolower(str[1]) != 'x')
		return (EXIT_FAILURE);
	i = 2;
	while (str[i] != '\0')
	{
		c = ft_tolower(str[i]);
		if (!ft_isdigit(str[i]) && !(c >= 'a' && c <= 'f'))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
