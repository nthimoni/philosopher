/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 16:44:52 by nthimoni          #+#    #+#             */
/*   Updated: 2022/02/22 05:48:18 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	log_action(philo->id, FORK, philo->info);
	pthread_mutex_lock(philo->r_fork);
	log_action(philo->id, FORK, philo->info);
	log_action(philo->id, EAT, philo->info);
	pthread_mutex_lock(&philo->m_last_eat);
	philo->last_eat = get_time(philo->info);
	pthread_mutex_unlock(&philo->m_last_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	usleep(philo->info->time_to_eat * 1000);
}
void	sleep_philo(t_philo *philo)
{
	log_action(philo->id, SLEEP, philo->info);
	usleep(philo->info->time_to_sleep * 1000);
}
void	think(t_philo *philo)
{
	log_action(philo->id, THINK, philo->info);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2)
		usleep(philo->info->time_to_eat * 1000);
	pthread_mutex_lock(&philo->info->mut_fin);
	while (!philo->info->is_finish)
	{
		pthread_mutex_unlock(&philo->info->mut_fin);
		eat(philo);
		sleep_philo(philo);
		think(philo);
		pthread_mutex_lock(&philo->info->mut_fin);
	}
	pthread_mutex_unlock(&philo->info->mut_fin);
	return (NULL);
}
