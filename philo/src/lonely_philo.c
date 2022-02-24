/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lonely_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:50:36 by nthimoni          #+#    #+#             */
/*   Updated: 2022/02/23 16:06:37 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	lonely_philo(t_info *info, t_philo *philo)
{
	log_action(1, FORK, info);
	printf("[%4d ms] %3d  \033[1;31mdied\n\033[0m", info->time_to_die + 1, 1);
	destroy_mutex(info, philo);
	return (0);
}
