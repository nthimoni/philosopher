/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 03:20:38 by nthimoni          #+#    #+#             */
/*   Updated: 2022/03/16 06:21:17 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	not_end(t_sem_val *end_sem)
{
	int	tmp;

	sem_wait(end_sem->sem_end_process);
	tmp = end_sem->end_process;
	sem_post(end_sem->sem_end_process);
	return (tmp);
}

void	is_dead(t_info *info, t_sem_val *end_sem)
{
	if (get_time(info) - info->last_eat > info->time_to_die)
	{
		if (!not_end(end_sem))
			log_action(info->id, DIE, info);
		sem_post(info->fini_sem);
		usleep(3000);
	}
}

void	smart_sleep(t_info *info, int duree_ms, t_sem_val *val)
{
	int	time;

	time = get_time(info);
	while(get_time(info) - time < duree_ms)
	{
		usleep(1000);
		is_dead(info, val);
	}
}

void	eat(t_info *info, t_sem_val *val)
{
	sem_wait(info->forks);
	sem_wait(info->forks);
	log_action(info->id, FORK, info);
	log_action(info->id, FORK, info);
	log_action(info->id, EAT, info);
	//sem_post(info->nb_meal);
	info->last_eat = get_time(info);
	smart_sleep(info, info->time_to_eat, val);
	sem_post(info->forks);
	sem_post(info->forks);
}
void	sleep_philo(t_info *info, t_sem_val *val)
{
	log_action(info->id, SLEEP, info);
	smart_sleep(info, info->time_to_sleep, val);
}

void	*kill_process(void *sem)
{
	t_sem_val	*val;

	val = sem;
	sem_wait(val->info->nb_process_to_kill);
	sem_wait(val->sem_end_process);
	val->end_process = 1;
	sem_post(val->sem_end_process);
	return (NULL);
}

void	routine(t_info *info)
{
	t_sem_val	end_sem;
	pthread_t	thread;

	end_sem.info = info;
	end_sem.end_process = 0;
	end_sem.sem_end_process = sem_open("/end_sem", O_CREAT, 0644, 1);
	pthread_create(&thread, NULL, kill_process, &end_sem);
	while (!not_end(&end_sem))
	{
		if (!not_end(&end_sem))
			eat(info, &end_sem);
		is_dead(info, &end_sem);
		if (!not_end(&end_sem))
			sleep_philo(info, &end_sem);
		is_dead(info, &end_sem);
		if (!not_end(&end_sem))
			log_action(info->id, THINK, info);
		is_dead(info, &end_sem);
	}
	pthread_join(thread, NULL);
	sem_close(info->fini_sem);
	sem_close(info->forks);
	//sem_close(info->nb_meal);
	sem_close(info->nb_process_to_kill);
	sem_close(end_sem.sem_end_process);
}
