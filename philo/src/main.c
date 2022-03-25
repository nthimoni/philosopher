/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:40:10 by nthimoni          #+#    #+#             */
/*   Updated: 2022/03/25 04:05:02 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "philo.h" 

int	destroy_mutex(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		pthread_mutex_destroy(philo[i].l_fork);
		pthread_mutex_destroy(&philo[i].m_last_eat);
		i++;
	}
	free(philo);
	free(info->fork);
	pthread_mutex_destroy(&info->mut_fin);
	return (0);
}

int	all_ate_enough(t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		pthread_mutex_lock(&philo[i].m_last_eat);
		if (philo[i].nb_of_eat < info->nb_eat || info->nb_eat == -1)
		{
			pthread_mutex_unlock(&philo[i].m_last_eat);
			return (0);
		}
		pthread_mutex_unlock(&philo[i].m_last_eat);
		i++;
	}
	return (1);
}

int	is_dead(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		pthread_mutex_lock(&philo[i].m_last_eat);
		if (get_time(info) - philo[i].last_eat > info->time_to_die + 1)
		{
			pthread_mutex_lock(&info->mut_fin);
			info->is_finish = 1;
			pthread_mutex_unlock(&info->mut_fin);
			pthread_mutex_unlock(&philo[i].m_last_eat);
			return (philo[i].id);
		}
		pthread_mutex_unlock(&philo[i].m_last_eat);
		if (all_ate_enough(philo, info))
		{
			pthread_mutex_lock(&info->mut_fin);
			info->is_finish = 1;
			pthread_mutex_unlock(&info->mut_fin);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	init_thread(pthread_t **thread, t_philo *philo, int nb)
{
	int	i;

	*thread = malloc(sizeof(pthread_t) * nb);
	if (!*thread)
		return (-1);
	i = 0;
	while (i < nb)
	{
		philo[i].nb_of_eat = 0;
		pthread_create((*thread) + i, NULL, routine, philo + i);
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_info		info;
	t_philo		*philo;
	pthread_t	*thread;
	int			dead_philo_id;

	if (error_parse(parse(argc, argv, &info)))
		return (-1);
	if (init_mutex(&info, &philo))
		return (-2);
	if (info.nb_philo == 1 || info.nb_philo == 0)
		return (lonely_philo(&info, philo));
	init_thread(&thread, philo, info.nb_philo);
	dead_philo_id = is_dead(&info, philo);
	while (!dead_philo_id)
	{
		usleep(10);
		dead_philo_id = is_dead(&info, philo);
	}
	if (dead_philo_id != -1)
		log_action(dead_philo_id, DIE, &info);
	join_thread(thread, info.nb_philo);
	destroy_mutex(&info, philo);
	free(thread);
}
