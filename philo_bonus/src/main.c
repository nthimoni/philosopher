/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 02:04:19 by nthimoni          #+#    #+#             */
/*   Updated: 2022/03/26 06:38:57 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	ft_init_sem(t_info *info)
{
	t_allsem	*sem;

	sem = info->sem;
	info->sem->forks = sem_open("/forks_philo",
			O_CREAT, S_IRWXU, info->nb_philo);
	sem_unlink("/forks_philo");
	info->sem->ate_enough = sem_open("/ate_enough", O_CREAT, S_IRWXU, 0);
	sem_unlink("/ate_enough");
	info->sem->dead_cond = sem_open("/dead_cond_philo", O_CREAT, S_IRWXU, 1);
	sem_unlink("/dead_cond_philo");
	info->sem->time_to_die = sem_open("/time_to_die_philo",
			O_CREAT, S_IRWXU, 0);
	sem_unlink("/time_to_die_philo");
	if (!sem->ate_enough || !sem->dead_cond || !sem->forks || !sem->time_to_die)
		close_all_sem(sem, -1);
	return (0);
}

void	*check_meal(void *arg)
{
	int		count;
	t_info	*info;

	info = arg;
	count = 0;
	while (count < info->nb_philo && !is_dead(info))
	{
		sem_wait(info->sem->ate_enough);
		count++;
	}
	if (count != info->nb_philo)
		return (NULL);
	sem_wait(info->sem->dead_cond);
	info->nb_philo++;
	while (info->nb_philo)
	{
		sem_post(info->sem->time_to_die);
		info->nb_philo--;
	}
	usleep(800000);
	sem_post(info->sem->dead_cond);
	return (NULL);
}

void	main_routine(t_info *info)
{	
	pthread_t	thread;
	pthread_t	check_meal_t;

	info->sem->last_eat = NULL;
	info->sem->finish_val = sem_open("/finish_val_main",
			O_CREAT, S_IRWXU, 1);
	sem_unlink("/finish_val_main");
	info->id = -1;
	if (info->sem->finish_val == SEM_FAILED)
		kill_all_philos(info->sem, -1, info->nb_philo);
	if (pthread_create(&thread, NULL, wait_death, info)
		|| pthread_create(&check_meal_t, NULL, check_meal, info))
		kill_all_philos(info->sem, -2, info->nb_philo);
	while (!is_dead(info))
		usleep(100000);
	pthread_join(thread, NULL);
	pthread_join(check_meal_t, NULL);
}

int	fork_philo(t_info *info)
{
	int	nb_fork;
	int	pid;

	nb_fork = 0;
	pid = 1;
	while (pid != 0 && nb_fork < info->nb_philo)
	{
		info->id = nb_fork + 1;
		pid = fork();
		nb_fork++;
		if (pid == -1)
			kill_all_philos(info->sem, -10, nb_fork);
	}
	if (pid == 0)
		routine(info);
	else
		main_routine(info);
	return (pid);
}

int	main(int argc, char *argv[])
{
	t_info		info;
	t_allsem	sem;

	info.sem = &sem;
	if (error_parse(parse(argc, argv, &info)))
		return (-1);
	ft_init_sem(&info);
	fork_philo(&info);
	close_all_sem(info.sem, 0);
	return (0);
}
