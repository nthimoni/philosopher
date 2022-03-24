/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 06:04:49 by nthimoni          #+#    #+#             */
/*   Updated: 2022/03/24 06:07:03 by nthimoni         ###   ########.fr       */
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
