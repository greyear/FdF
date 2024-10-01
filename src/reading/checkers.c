/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:25:22 by azinchen          #+#    #+#             */
/*   Updated: 2024/10/01 19:39:03 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

//zapataya + color

int	num_check(char *str)
{
	int	i;
	while (str[i] != '\n' && str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && !ft_issign(str[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

/*
0x + 6 or 8 digits in hexadecimal - okay, convert into color
the other amount - exit with error

*/

