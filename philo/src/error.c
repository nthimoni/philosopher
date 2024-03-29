/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:12:52 by nthimoni          #+#    #+#             */
/*   Updated: 2022/03/25 03:23:11 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	error_parse(int err)
{
	if (!err)
		return (0);
	printf("\033[0;31m");
	if (err == -1)
		printf("Nombre d'arguments incorrect !\n");
	else if (err == -2)
		printf("Argument(s) invalide(s) !\n");
	else if (err == -3)
		printf("Erreur lors de l'acces a l'horloge !\n");
	return (-1);
}
