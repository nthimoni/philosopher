/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 06:04:49 by nthimoni          #+#    #+#             */
/*   Updated: 2022/03/26 06:38:44 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_info *info)
{
	sem_wait(info->sem->finish_val);
	if (info->is_finish)
	{
		sem_post(info->sem->finish_val);
		return (1);
	}
	sem_post(info->sem->finish_val);
	return (0);
}

void	smart_sleep(t_info *info, int duree_ms)
{
	int	time;

	time = get_time(info);
	while (get_time(info) - time < duree_ms)
	{
		usleep(1000);
		if (is_dead(info))
			break ;
	}
}

void	close_all_sem(t_allsem *sem, int code)
{
	if (sem->ate_enough != SEM_FAILED)
		sem_close(sem->ate_enough);
	if (sem->dead_cond != SEM_FAILED)
		sem_close(sem->dead_cond);
	if (sem->finish_val != SEM_FAILED)
		sem_close(sem->finish_val);
	if (sem->forks != SEM_FAILED)
		sem_close(sem->forks);
	if (sem->time_to_die != SEM_FAILED)
		sem_close(sem->time_to_die);
	if (sem->last_eat != SEM_FAILED)
		sem_close(sem->last_eat);
	exit(code);
}

void	kill_all_philos(t_allsem *sem, int code, int nb_philos)
{
	int	i;

	i = 0;
	while (i++ < nb_philos)
		sem_post(sem->time_to_die);
	if (code == -1)
		printf("FORK FAILED!");
	close_all_sem(sem, code);
}

void	ft_bzero(void *pointer, size_t count)
{
	char	*ptr;

	ptr = (char *)pointer;
	while (count--)
		ptr[count] = 0;
}
