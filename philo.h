/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:42:42 by msacaliu          #+#    #+#             */
/*   Updated: 2024/04/15 18:06:41 by msacaliu         ###   ########.fr       */
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

typedef pthread_mutex_t t_mtx;
typedef	struct s_data t_data;


typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
} t_fork;



typedef struct s_philo
{
	int		id;
	long	meal_counter;
	bool	full;
	long	last_meal_time;
	t_fork *first_fork;
	t_fork	*second_fork;
	pthread_t	thread_id; //philo
	t_data		*data;
	
} t_philo;

typedef struct s_data // container of all data
{
	long	philo_nb;
	long	time_to_sleep;
	long	time_to_eat;
	long	time_to_die;
	long	limit_meals;
	long	start_simulation;
	bool	end_simulation; //triggerd when a philo dies or all meals are eaten;
	t_fork	*forks; // the array of forks;
	t_philo	*philos; // array of philos;
	bool	all_threads_ready; //syncronize philosophers
} t_data;


			// utils 
long	ft_atoi(char *str);
			// input validation
bool		validate_input(t_data *table, char *argv[], int argc);
		// actual dinner
void	start_dinner(t_data *data);

#endif