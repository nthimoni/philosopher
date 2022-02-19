/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:28:10 by nthimoni          #+#    #+#             */
/*   Updated: 2022/02/19 15:53:25 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

long int	ft_atol(const char *str)
{
	int			signe;
	long int	ret;
	int			i;

	i = 0;
	signe = 1;
	ret = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		signe = -signe;
	}
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret *= 10;
		ret += str[i] - '0';
		i++;
	}
	return (ret * signe);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int is_valid_uint(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (i > 10 || i == 0)
		return (0);
	if (ft_atol(str) > INT_MAX)
		return (0);
	return (1);
}
