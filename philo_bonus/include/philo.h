/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <nthimoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 02:13:20 by nthimoni          #+#    #+#             */
/*   Updated: 2022/03/14 05:32:06 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_info
{
	int		nb_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_eat;
	int		last_eat;
	long	start_time;
	int		is_finish;
	int		*pid;
	sem_t	*fini_sem;
	sem_t	*forks;
	sem_t	*nb_meal;
	sem_t	*nb_process_to_kill;
	int		id;
}	t_info;

typedef struct	s_sem_val
{
	int		end_process;
	sem_t	*sem_end_process;
	t_info	*info;
}	t_sem_val;

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
void	routine(t_info *info);

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

#endif
