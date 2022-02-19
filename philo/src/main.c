/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:40:10 by nthimoni          #+#    #+#             */
/*   Updated: 2022/02/19 18:03:42 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include "philo.h" 


int init_mutex(t_info *info, t_philo *philo)
{
	int	i;

	pthread_mutex_init(&info, NULL);
	philo = malloc(sizeof(t_philo) * info->nb_philo);
	i = 0;

	while (i < info->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].last_eat = 0;
		i++;
	}
}

int	destroy_mutex(t_info *info, t_philo *philo)
{
	pthread_mutex_destroy(&info);
}

int main(int argc, char *argv[])
{
	int old;
	int tmp;
	t_info info;

	old = 0;
	if (error_parse(parse(argc, argv, &info)))
		return (-1);
	while (info->is_finish == 0)
	{
		pthread_mutex_unlock(&info->mut_fin);
		usleep(2);
		pthread_mutex_lock(&info->mut_fin);
	}
}
