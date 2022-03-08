/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <nthimoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 02:05:54 by nthimoni          #+#    #+#             */
/*   Updated: 2022/03/08 03:04:40 by nthimoni         ###   ########.fr       */
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
	info->nb_eat = -1;
	if (argc == 6)
		info->nb_eat = ft_atol(argv[5]);
	if (init_time(info) == -1)
		return (-3);
	info->fini = sem_open("fini", O_CREAT, S_IRWXU, 0);
	if (info->fini == SEM_FAILED)
		return (-4);
	return (0);
}
