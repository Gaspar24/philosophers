/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:42:42 by msacaliu          #+#    #+#             */
/*   Updated: 2024/04/12 15:22:14 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <stdbool.h>

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*lock;
	int				ph_num;
	int				id;
	int				l_fork;
	int				r_fork;
	int				meal_num;
	int				eating;
	int				dead;
	int				sleeping;
	int				thinking;
	int				total_meals;
	long long		start;
	long long		last_meal;
	long long		eat_timer;
	long long		die_timer;
	long long		slp_timer;
}	t_philo;

long	ft_atoi(char *str);
int		check_args(int argc, char *argv[], t_philo *philo);
t_philo	*create_philosophers(int num_philos);
long long	get_time(void);



#endif