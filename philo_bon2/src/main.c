/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 02:04:19 by nthimoni          #+#    #+#             */
/*   Updated: 2022/03/20 23:36:10 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_meal_count(void	*arg)
{
	t_info	*info;
	int		count;

	info = arg;
	count = 0;
	while (count < info->nb_philo * info->nb_eat)
	{
		sem_wait(info->nb_meal);
		count++;
	}
	sem_post(info->fini_sem);
	return (NULL);
}

void	kill_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		sem_post(info->nb_process_to_kill);
		i++;
	}
}

int main(int argc, char *argv[])
{
	t_info	info;
	int		pid;
	int		nb_fork;

	//info.nb_meal = sem_open("/nb_meal", O_CREAT, 0644, 0);
	//if (info.nb_meal == SEM_FAILED)
		//return (-1);
	sem_unlink("/nb_meal");
	info.nb_process_to_kill = sem_open("/process_to_kill", O_CREAT, 0644, 0);
	sem_unlink("/process_to_kill");
	info.fini_sem = sem_open("/cfini", O_CREAT, 0644, 0);
	sem_unlink("/cfini");
	if (error_parse(parse(argc, argv, &info)) || info.fini_sem == SEM_FAILED)
		return (-1);
	info.forks = sem_open("/allforks", O_CREAT, S_IRWXU, info.nb_philo);
	sem_unlink("/allforks");
	info.pid = malloc(sizeof(int) * info.nb_philo);
	if (info.forks == SEM_FAILED || !info.pid)
	{
		printf("Erreur lors de l'allocation de la memoire\n");
		return (-1);
	}
	pid = 1;
	nb_fork = 0;
	info.last_eat = 0;
	while (pid != 0 && nb_fork < info.nb_philo)
	{
		pid = fork();
		info.pid[nb_fork] = pid;
		info.id = nb_fork + 1;
		nb_fork++;
	}
	if (pid == 0)
	{
		free(info.pid);
		routine(&info);
	}
	else
	{
		sem_wait(info.fini_sem);
		kill_philos(&info);
		sem_close(info.fini_sem);
		sem_close(info.forks);
		sem_close(info.nb_process_to_kill);
		free(info.pid);
	}
	return (0);
}
