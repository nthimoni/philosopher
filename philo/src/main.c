/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:40:10 by nthimoni          #+#    #+#             */
/*   Updated: 2022/02/20 19:08:13 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include "philo.h" 


int init_mutex(t_info *info, t_philo **philo)
{
	int	i;

	pthread_mutex_init(&info, NULL);
	*philo = malloc(sizeof(t_philo) * info->nb_philo);
	if (!philo)
		return (-1);
	info->fork = malloc(sizeof(pthread_mutex_t) * info->nb_philo);
	if (!fork)
		return (-2);
	i = 0;
	while (i < info->nb_philo)
	{

		philo[i].id = i + 1;
		philo[i].last_eat = 0;
		philo[i].l_fork = &info->fork[i];
		if (i != 0)
			philo[i].r_fork = &info->fork[i - 1];
		else
			philo[i].r_fork = &info->fork[info->nb_philo - 1];
		i++;
	}
}

int	destroy_mutex(t_info *info, t_philo *philo)
{
	pthread_mutex_destroy(&info);
}

int	is_dead(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		if (get_time(info) - philo[i].last_eat > info->time_to_die)
		{
			info->is_finish = 1;
			log(philo[i].id, DIE);
			return (1);
		}
	}
	return (0);
}

int main(int argc, char *argv[])
{
	int		old;
	int		tmp;
	t_info	info;

	old = 0;
	if (error_parse(parse(argc, argv, &info)))
		return (-1);
	while (!is_dead(&info, philo))
		usleep(2);
}
