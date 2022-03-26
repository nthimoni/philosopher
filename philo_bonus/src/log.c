/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 16:52:33 by nthimoni          #+#    #+#             */
/*   Updated: 2022/03/24 06:02:20 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_action(int id, int action, t_info *info)
{
	if (is_dead(info))
		return ;
	if (action == FORK)
		printf("[%4ld ms] %3d  \033[1;33mhas taken a fork\033[0m\n",
			get_time(info), id);
	else if (action == EAT)
		printf("[%4ld ms] %3d  \033[1;32mis eating\033[0m\n",
			get_time(info), id);
	else if (action == SLEEP)
		printf("[%4ld ms] %3d  \033[1;36mis sleeping\033[0m\n",
			get_time(info), id);
	else if (action == THINK)
		printf("[%4ld ms] %3d  \033[1;35mis thinking\033[0m\n",
			get_time(info), id);
	else if (action == DIE)
		printf("[%4ld ms] %3d  \033[1;31mdied\033[0m\n",
			get_time(info), id);
}
