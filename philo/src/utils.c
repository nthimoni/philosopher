/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:28:10 by nthimoni          #+#    #+#             */
/*   Updated: 2022/03/25 04:00:19 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "philo.h"

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

int	is_valid_uint(char *str)
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

void	join_thread(pthread_t *thread, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
}

int	init_mutex(t_info *info, t_philo **philo)
{
	int	i;

	pthread_mutex_init(&info->mut_fin, NULL);
	*philo = malloc(sizeof(t_philo) * info->nb_philo);
	if (!*philo)
		return (-1);
	info->fork = malloc(sizeof(pthread_mutex_t) * info->nb_philo);
	if (!info->fork)
		return (-2);
	i = 0;
	while (i < info->nb_philo)
	{
		pthread_mutex_init(&(*philo)[i].m_last_eat, NULL);
		pthread_mutex_init(info->fork + i, NULL);
		(*philo)[i].id = i + 1;
		(*philo)[i].last_eat = 0;
		(*philo)[i].l_fork = &info->fork[i];
		(*philo)[i].info = info;
		if (i != 0)
			(*philo)[i].r_fork = &info->fork[i - 1];
		else
			(*philo)[i].r_fork = &info->fork[info->nb_philo - 1];
		i++;
	}
	return (0);
}
