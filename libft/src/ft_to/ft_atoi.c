/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:07:07 by azinchen          #+#    #+#             */
/*   Updated: 2024/04/24 17:28:56 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
static int	ft_is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static long	ft_is_sign(char c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}

int	ft_atoi(const char	*str)
{
	int		sign;
	int		i;
	long	res;
	long	prev;

	i = 0;
	sign = 1;
	while (ft_is_space(str[i]))
		i++;
	if (ft_is_sign(str[i]) && str[i++] == '-')
		sign = -1;
	res = 0;
	while (ft_is_num(str[i]))
	{
		prev = res;
		res = res * 10 + (str[i++] - '0');
		if (prev != res / 10 && sign == -1)
			return (0);
		if (prev != res / 10 && sign == 1)
			return (-1);
	}
	return ((int)sign * res);
}
