/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 16:44:52 by nthimoni          #+#    #+#             */
/*   Updated: 2022/02/19 18:16:12 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (get_time(philo->info) - philo->last_eat < philo->info->time_to_die)
	{
	}
	log(philo->id, DIE);
}
