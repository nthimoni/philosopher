/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <nthimoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 02:05:54 by nthimoni          #+#    #+#             */
/*   Updated: 2022/03/24 06:29:28 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse(int argc, char *argv[], t_info *info)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (-1);
	while (argv[i])
	{
		if (!is_valid_uint(argv[i]))
			return (-2);
		i++;
	}
	info->nb_philo = ft_atol(argv[1]);
	info->time_to_die = ft_atol(argv[2]);
	info->time_to_eat = ft_atol(argv[3]);
	info->time_to_sleep = ft_atol(argv[4]);
	info->max_meal = -1;
	info->nb_meal = 0;
	info->last_eat = 0;
	if (argc == 6)
		info->max_meal = ft_atol(argv[5]);
	if (init_time(info) == -1)
		return (-3);
	info->is_finish = 0;
	return (0);
}
