/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 16:52:33 by nthimoni          #+#    #+#             */
/*   Updated: 2022/02/22 18:24:47 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	log_action(int id, int action, t_info *info)
{
	pthread_mutex_lock(&info->mut_fin);
	if (info->is_finish == 0)
	{
		if (action == FORK)
			printf("[%4ld ms] %3d  \033[1;33mhas taken a fork\n\033[0m", get_time(info), id);
		else if (action == EAT)
			printf("[%4ld ms] %3d  \033[1;32mis eating\n\033[0m", get_time(info), id);
		else if (action == SLEEP)
			printf("[%4ld ms] %3d  \033[1;36mis sleeping\n\033[0m", get_time(info), id);
		else if (action == THINK)
			printf("[%4ld ms] %3d  \033[1;35mis thinking\n\033[0m", get_time(info), id);
	}
	pthread_mutex_unlock(&info->mut_fin);
	if (action == DIE)
		printf("[%4ld ms] %3d  \033[1;31mdied\n\033[0m", get_time(info), id);
}
