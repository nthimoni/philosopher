/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <nthimoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 02:13:20 by nthimoni          #+#    #+#             */
/*   Updated: 2022/03/24 01:03:54 by nthimoni         ###   ########.fr       */
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

typedef struct s_allsem
{
	sem_t	*forks;
	sem_t	*ate_enough;
	sem_t	*dead_cond;
	sem_t	*time_to_die;
	sem_t   *finish_val;
	sem_t	*last_eat;
}	t_allsem;

typedef struct	s_info
{
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			max_meal;
	int			nb_meal;
	int			last_eat;
	long		start_time;
	int			is_finish;
	int			id;
	t_allsem	*sem;
}	t_info;

// time.c
int init_time(t_info *info);
long get_time(t_info *info);

// parse.c
int	parse(int argc, char *argv[], t_info *info);

// error.c
int	error_parse(int err);

// utils.c
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int		is_valid_uint(char *str);
long	ft_atol(const char *str);

// log.c
void	log_action(int id, int action, t_info *info);

// routine.c
void	routine(t_info *info);
int		is_dead(t_info *info);

// detect_death.c
void	*detect_death(void *arg);
void	*wait_death(void *arg);

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

#endif
