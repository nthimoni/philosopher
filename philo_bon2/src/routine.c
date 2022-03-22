/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 03:20:38 by nthimoni          #+#    #+#             */
/*   Updated: 2022/03/22 06:52:35 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	is_dead(t_info *info)
{
	sem_wait(info->sem->finish_val);
	if (info->sem->finish_val)
	{
		sem_post(info->sem->finish_val);
		return (1);
	}
	sem_post(info->sem->finish_val);
	return (0);
}

void	smart_sleep(t_info *info, int duree_ms)
{
	int	time;

	time = get_time(info);
	while(get_time(info) - time < duree_ms)
	{
		usleep(1000);
		if (is_dead(info))
			break;
	}
}

void	eat(t_info *info)
{
	sem_wait(info->sem->forks);
	sem_wait(info->sem->dead_cond);
	log_action(info->id, FORK, info);
	sem_post(info->sem->dead_cond);
	sem_wait(info->sem->forks);
	log_action(info->id, FORK, info);
	sem_wait(info->sem->dead_cond);
	info->last_eat = get_time(info);
	info->nb_meal += 1;
	if (info->nb_meal == info->max_meal)
		sem_post(info->sem->ate_enough);
	log_action(info->id, EAT, info);
	sem_post(info->sem->dead_cond);
	smart_sleep(info, info->time_to_eat);
	sem_post(info->sem->forks);
	sem_post(info->sem->forks);
}

void	sleep_philo(t_info *info)
{
	sem_wait(info->sem->dead_cond);
	log_action(info->id, SLEEP, info);
	sem_post(info->sem->dead_cond);
	smart_sleep(info, info->time_to_sleep);
}

void	routine(t_info *info)
{
	while (!is_dead(info))
	{
		eat(info);
		sleep_philo(info);
		sem_wait(info->sem->dead_cond);
		log_action(info->id, THINK, info);
		sem_close(info->sem->dead_cond);;
	}
}
