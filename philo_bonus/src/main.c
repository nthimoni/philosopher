/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 02:04:19 by nthimoni          #+#    #+#             */
/*   Updated: 2022/03/08 03:19:55 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{
	t_info	info;
	int		pid;
	int		nb_fork;

	if (error_parse(parse(argc, argv, &info)))
		return (-1);
	info->fork = sem_open("fork", O_CREAT, S_IRWXU, info->nb_philo);
	if (info->fork == SEM_FAILED)
	{
		printf("Erreur lors de l'initialisation d'un semaphore\n");
		return (-1);
	}
	pid = 1;
	nb_fork = 0;
	while (pid != 0 && nb_fork < info->nb_philo)
	{
		pid = fork();
		nb_fork++;
	}
	if (pid == 0)
		routine();
	else
	{
		sem_wait(info->fini);
		sem_close(info->fini);
		sem_close(info->forks);
	}
	return (0);
}
