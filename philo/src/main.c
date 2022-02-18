/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:40:10 by nthimoni          #+#    #+#             */
/*   Updated: 2022/02/16 15:40:07 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>

void	*print(void	*arg)
{
	(void)arg;
	while (1)
		printf("OK\n");
	return NULL;
}

void	*print2(void *arg)
{
	(void)arg;
	while (1)
		printf("OK2\n");
	return NULL;
}

int main()
{
	pthread_t res;
	pthread_t res2;

	pthread_create(&res, NULL, print, NULL);
	pthread_create(&res2, NULL, print2, NULL);
	pthread_join(res, NULL);
	pthread_join(res2, NULL);
}
