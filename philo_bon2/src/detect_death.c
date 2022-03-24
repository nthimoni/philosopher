/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_death.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 06:16:12 by nthimoni          #+#    #+#             */
/*   Updated: 2022/03/24 06:36:18 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*wait_death(void *arg)
{
	t_info	*info;

	info = arg;
	sem_wait(info->sem->time_to_die);
	sem_wait(info->sem->finish_val);
	info->is_finish = 1;
	sem_post(info->sem->finish_val);
	return (NULL);
}

void	*detect_death(void *arg)
{
	t_info	*info;

	info = arg;
	sem_wait(info->sem->dead_cond);
	sem_wait(info->sem->last_eat);
	while (get_time(info) - info->last_eat < info->time_to_die)
	{
		sem_post(info->sem->last_eat);
		sem_post(info->sem->dead_cond);
		usleep(100);
		sem_wait(info->sem->dead_cond);
		sem_wait(info->sem->last_eat);
	}
	sem_post(info->sem->last_eat);
	log_action(info->id, DIE, info);
	sem_post(info->sem->ate_enough);
	info->nb_philo++;
	while (info->nb_philo)
	{
		sem_post(info->sem->time_to_die);
		info->nb_philo--;
	}
	usleep(20000);
	sem_post(info->sem->dead_cond);
	return (NULL);
}
