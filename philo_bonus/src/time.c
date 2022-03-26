/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <nthimoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:31:10 by nthimoni          #+#    #+#             */
/*   Updated: 2022/03/24 05:54:46 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include "philo.h"

int	init_time(t_info *info)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	info->start_time = (tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
	return (0);
}

long	get_time(t_info *info)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - info->start_time);
}
