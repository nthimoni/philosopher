/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <nthimoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 02:05:54 by nthimoni          #+#    #+#             */
/*   Updated: 2022/02/19 15:39:55 by nthimoni         ###   ########.fr       */
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
	(void)info;
	return (0);
}
