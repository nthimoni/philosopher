/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 03:20:38 by nthimoni          #+#    #+#             */
/*   Updated: 2022/03/26 06:10:50 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	eat(t_info *info)
{
	sem_wait(info->sem->forks);
	sem_wait(info->sem->dead_cond);
	log_action(info->id, FORK, info);
	sem_post(info->sem->dead_cond);
	sem_wait(info->sem->forks);
	sem_wait(info->sem->dead_cond);
	log_action(info->id, FORK, info);
	info->last_eat = get_time(info);
	info->nb_meal += 1;
	if (info->nb_meal == info->max_meal && info->max_meal != -1)
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

void	generate_name(char *buf, int id, char *pref)
{
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(pref);
	ft_strlcpy(buf, pref, len);
	while (i < 6)
	{
		buf[len + i] = (id % 10) + '0';
		id /= 10;
		i++;
	}
	buf[len + i] = '\0';
}

int	create_sem(t_info *info)
{
	char	buf[20];

	generate_name(buf, info->id, "/finish_val");
	info->sem->finish_val = sem_open(buf, O_CREAT, S_IRWXU, 1);
	sem_unlink(buf);
	generate_name(buf, info->id, "/last_eat");
	info->sem->last_eat = sem_open(buf, O_CREAT, S_IRWXU, 1);
	sem_unlink(buf);
	if (info->sem->finish_val == SEM_FAILED
		|| info->sem->last_eat == SEM_FAILED)
		kill_all_philos(info->sem, -3, info->nb_philo);
	return (0);
}

void	routine(t_info *info)
{
	pthread_t	detect;
	pthread_t	wait;

	create_sem(info);
	if (pthread_create(&wait, NULL, wait_death, info)
		|| pthread_create(&detect, NULL, detect_death, info))
		kill_all_philos(info->sem, -4, info->nb_philo);
	if (info->id % 2 == 0)
		smart_sleep(info, info->time_to_eat / 2);
	while (!is_dead(info))
	{
		eat(info);
		sleep_philo(info);
		sem_wait(info->sem->dead_cond);
		log_action(info->id, THINK, info);
		sem_post(info->sem->dead_cond);
	}
	pthread_join(wait, NULL);
	pthread_join(detect, NULL);
}
