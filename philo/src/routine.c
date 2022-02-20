/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 16:44:52 by nthimoni          #+#    #+#             */
/*   Updated: 2022/02/20 18:32:56 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (!philo->info->is_finish)
	{
		pthread_mutex_unlock(&info->mut_fin);
		
		pthread_mutex_lock(&info->mut_fin);
	}
}
