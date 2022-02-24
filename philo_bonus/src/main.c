/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:40:10 by nthimoni          #+#    #+#             */
/*   Updated: 2022/02/23 16:06:09 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "philo.h" 


int init_mutex(t_info *info, t_philo **philo)
{
	int	i;

	pthread_mutex_init(&info->mut_fin, NULL);
	*philo = malloc(sizeof(t_philo) * info->nb_philo);
	if (!*philo)
		return (-1);
	info->fork = malloc(sizeof(pthread_mutex_t) * info->nb_philo);
	if (!info->fork)
		return (-2);
	i = 0;
	while (i < info->nb_philo)
	{
		pthread_mutex_init(&(*philo)[i].m_last_eat, NULL);
		pthread_mutex_init(info->fork + i, NULL);
		(*philo)[i].id = i + 1;
		(*philo)[i].last_eat = 0;
		(*philo)[i].l_fork = &info->fork[i];
		(*philo)[i].info = info;
		if (i != 0)
			(*philo)[i].r_fork = &info->fork[i - 1];
		else
			(*philo)[i].r_fork = &info->fork[info->nb_philo - 1];
		i++;
	}
	return (0);
}

int	destroy_mutex(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		pthread_mutex_destroy(philo[i].l_fork);
		pthread_mutex_destroy(&philo[i].m_last_eat);
		i++;
	}
	free(philo);
	free(info->fork);
	pthread_mutex_destroy(&info->mut_fin);
	return (0);
}

int	is_dead(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		pthread_mutex_lock(&philo[i].m_last_eat);
		if (get_time(info) - philo[i].last_eat > info->time_to_die)
		{
			pthread_mutex_lock(&info->mut_fin);
			info->is_finish = 1;
			pthread_mutex_unlock(&info->mut_fin);
			pthread_mutex_unlock(&philo[i].m_last_eat);
			return (philo[i].id);
		}
		if (philo[i].nb_of_eat >= info->nb_eat && info->nb_eat != -1)
		{
			pthread_mutex_lock(&info->mut_fin);
			info->is_finish = 1;
			pthread_mutex_unlock(&info->mut_fin);
			pthread_mutex_unlock(&philo[i].m_last_eat);
			return (-1);
		}
		pthread_mutex_unlock(&philo[i].m_last_eat);
		i++;
	}
	return (0);
}

int	init_thread(pthread_t **thread, t_philo *philo, int nb)
{
	int	i;

	*thread = malloc(sizeof(pthread_t) * nb);
	if (!*thread)
		return (-1);
	i = 0;
	while (i < nb)
	{
		pthread_create((*thread) + i, NULL, routine, philo + i);
		i++;
	}
	return (0);
}

void	join_thread(pthread_t *thread, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
}

int main(int argc, char *argv[])
{
	t_info		info;
	t_philo		*philo;
	pthread_t	*thread;
	int			dead_philo_id;

	if (error_parse(parse(argc, argv, &info)))
		return (-1);
	if (init_mutex(&info, &philo))
		return (-2);
	if (info.nb_philo == 1)
		return (lonely_philo(&info, philo));
	init_thread(&thread, philo, info.nb_philo);
	dead_philo_id = is_dead(&info, philo);
	while (!dead_philo_id)
	{
		usleep(10);
		dead_philo_id = is_dead(&info, philo);
	}
	if (dead_philo_id != -1)
		log_action(dead_philo_id, DIE, &info);
	join_thread(thread, info.nb_philo);
	destroy_mutex(&info, philo);
	free(thread);
}
