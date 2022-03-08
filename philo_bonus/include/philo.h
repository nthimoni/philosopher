/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <nthimoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 02:13:20 by nthimoni          #+#    #+#             */
/*   Updated: 2022/03/08 03:26:24 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <semaphore.h>

typedef struct	s_info
{
	int		nb_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_eat;
	long	start_time;
	sem_t	*fini;
	sem_t	*forks;
	int		id;
}	t_info;

// time.c
int init_time(t_info *info);
long get_time(t_info *info);

// parse.c
int	parse(int argc, char *argv[], t_info *info);

// error.c
int	error_parse(int err);

// utils.c
int		is_valid_uint(char *str);
long	ft_atol(const char *str);

// log.c
void	log_action(int id, int action, t_info *info);

// routine.c
void	*routine(void *arg);

// lonely_philo.c
int	lonely_philo(t_info *info, t_philo *philo);
int		destroy_mutex(t_info *info, t_philo *philo);

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

#endif
