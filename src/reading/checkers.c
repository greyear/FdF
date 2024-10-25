/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:25:22 by azinchen          #+#    #+#             */
/*   Updated: 2024/10/04 15:20:55 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static int	overflow_check(char *str)
{
	long	sign;
	int		i;
	long	res;

	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (ft_issign(str[i]) && str[i++] == '-')
		sign = -1;
	res = 0;
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i++] - '0');
		if (res * sign < (long)INT_MIN || res * sign > (long)INT_MAX)
			return (EXIT_FAILURE);
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
	if (ft_issign(str[0]) && (!ft_isdigit(str[1]) || str[1] == '\0'))
		return (EXIT_FAILURE);
	i = 1;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (EXIT_FAILURE);
		i++;
	}
	if (overflow_check(str))
		return (EXIT_FAILURE);
	value = ft_atoi(str);
	if (value < INT_MIN || value > INT_MAX)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	color_check(char *str)
{
	int		i;
	char	c;
	int		len;

	if (!str)
		return (EXIT_FAILURE);
	len = color_len(str);
	if (!(len == 10 || len == 8 || len == 6 || len == 4))
		return (EXIT_FAILURE);
	if (str[0] != '0' || ft_tolower(str[1]) != 'x')
		return (EXIT_FAILURE);
	i = 2;
	while (str[i] != '\0' && str[i] != '\n')
	{
		c = ft_tolower(str[i]);
		if (!ft_isdigit(str[i]) && !(c >= 'a' && c <= 'f'))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
