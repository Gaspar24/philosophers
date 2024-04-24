/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:42:42 by msacaliu          #+#    #+#             */
/*   Updated: 2024/04/24 14:23:17 by msacaliu         ###   ########.fr       */
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




//PHILO STATUS

typedef	enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
} t_philo_status;

typedef enum time_code
{
	SECOND,
	MILISECOND,
	MICROSECOND,
}	t_time_code;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
} t_fork;



typedef struct s_philo
{
	int		id;
	bool	dead;
	long	meal_counter;
	bool	full;
	long	last_meal_time;
	t_fork *first_fork;
	t_fork	*second_fork;
	pthread_t	thread_id; //philo
	t_data		*data;
	t_mtx		philo_mutex; // useful for races with monitor
	
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
	t_mtx	data_mutex; //avoid races
	t_mtx	write_mutex; // write state
	pthread_t monitor; // chek for died philos
} t_data;

			// utils 
long		ft_atoi(char *str);
long		get_time(t_time_code time_code);
void		mod_usleep(long usec, t_data *data);
			// input validation
bool		validate_input(t_data *table, char *argv[], int argc);
			// data_intit
bool		data_init(t_data *data);
			// actual dinner
void		start_dinner(t_data *data);
			// getters and setters
void		set_bool(t_mtx *mutex, bool *dest, bool value);
bool		get_bool(t_mtx *mutex, bool *value);
void		set_long(t_mtx *mutex, long *dest, long value);
long		get_long(t_mtx *mutex, long *value);
bool		simulation_finished(t_data *data);
			/// syncro utils
void		wait_all_threads(t_data *data);
			/// write_status
void		write_status(t_philo_status status,t_philo *philo);
			//monitor
void		*monitor_dinner(t_philo *philo);



#endif