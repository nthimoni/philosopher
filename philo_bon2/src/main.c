/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 02:04:19 by nthimoni          #+#    #+#             */
/*   Updated: 2022/03/24 00:59:15 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int init_sem(t_info *info)
{
	info->sem->forks = sem_open("/forks_philo", O_CREAT, S_IRWXU, info->nb_philo);
	sem_unlink("/forks_philo");
	info->sem->ate_enough = sem_open("/ate_enough", O_CREAT, S_IRWXU, 0);
	sem_unlink("/ate_enough");
	info->sem->dead_cond = sem_open("/dead_cond_philo", O_CREAT, S_IRWXU, 1);
	sem_unlink("/dead_cond_philo");
	info->sem->time_to_die = sem_open("/time_to_die_philo", O_CREAT, S_IRWXU, 0);
	sem_unlink("/time_to_die_philo");
	return (0);
}

void *check_meal()
{
	//TODO
	return (NULL);
}

int main(int argc, char *argv[])
{
	t_info	info;
	int		pid;
	int		nb_fork;

	if (error_parse(parse(argc, argv, &info)))
		return (-1);
	init_sem(&info);
	pid = 1;
	nb_fork = 0;
	info.last_eat = 0;
	while (pid != 0 && nb_fork < info.nb_philo)
	{
		pid = fork();
		info.id = nb_fork + 1;
		nb_fork++;
	}
	if (pid == 0)
	{
		routine(&info);
		sem_close(info.sem->last_eat);
	}
	else
		while (!is_dead(&info))
			usleep(1000000);
	sem_close(info.sem->ate_enough);
	sem_close(info.sem->dead_cond);
	sem_close(info.sem->finish_val);
	sem_close(info.sem->forks);
	sem_close(info.sem->time_to_die);
	return (0);
}
