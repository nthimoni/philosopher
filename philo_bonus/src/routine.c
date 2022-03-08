/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 03:20:38 by nthimoni          #+#    #+#             */
/*   Updated: 2022/03/08 03:28:23 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	eat(t_info *info)
{
	sem_wait(info->forks);
	sem_wait(info->forks);
	log_action(info->id, FORK, info);
	log_action(info->id, FORK, info);
	sem_post(info->forks);
	sem_post(info->forks);
}
void	sleep_philo(t_info *info)
{
	log_action(philo->id, SLEEP, info);
	usleep(info->time_to_sleep * 1000);
}
void	think(t_philo *philo)
{
	log_action(info->id, THINK, philo->info);
}

void	routine(t_info *info)
{
	t_philo	*philo;

	philo = arg;
	if (info->id % 2)
		usleep(info->time_to_eat * 1000);
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
