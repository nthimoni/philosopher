/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <nthimoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 02:13:20 by nthimoni          #+#    #+#             */
/*   Updated: 2022/02/20 16:32:18 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

typedef struct	s_info
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	long			start_time;
	int				is_finish;
	pthread_mutex_t	mut_fin;
	pthread_mutex_t	*mut_fork;
}	t_info;

typedef struct	s_philo
{
	int				id;
	int				last_eat;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

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
void	log(int id, int action);
# define FORK
# define EAT
# define SLEEP
# define THINK
# define DIE

#endif
