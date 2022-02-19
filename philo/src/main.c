/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:40:10 by nthimoni          #+#    #+#             */
/*   Updated: 2022/02/19 15:42:48 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include "philo.h" 


int main(int argc, char *argv[])
{
	int old;
	int tmp;
	t_info info;

	old = 0;
	if (error_parse(parse(argc, argv, &info)))
		return (-1);
	init_time(&info);
	while (1)
	{
		tmp = get_time(&info);
		if (tmp / 1000.0f > old + 1)
		{
			old = tmp / 1000;
			printf("%d \n", old);
		}
	}
}
