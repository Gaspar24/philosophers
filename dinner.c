/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:48:27 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/03 17:47:04 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

	//same algo but..
	// 1)fake to lock the fork
	// 2) sleep until the monitor will bust it

void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// wait_all_threads(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILISECOND));
	write_status(TAKE_FIRST_FORK, philo);
	// write_status(DIED,philo);
	while (!simulation_finished(philo->data))
		usleep(100);
	return (NULL);
}

	// THINKING routine  
void	thinking(t_philo *philo, bool pre_simulation) 
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simulation)	
		write_status(THINKING,philo);
	// if the system is even , we don t care, system already fair
	if (philo->data->philo_nb % 2 == 0)
		return ;
	// odd, not always fair
	t_eat = philo->data->time_to_eat;
	t_sleep = philo->data->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	// precise control in want to make;
	mod_usleep(t_think, philo->data);
}


	// EAT routine
		// 1. grab the forks;
		// 2.eating : write eat, update last meal, update meals counter, bool full if needed
		// 3.realease the forks
		
static	void	eat(t_philo *philo)
{
	//1. getting the forks
	pthread_mutex_lock(&philo->first_fork->fork); // Lock first fork
	write_status(TAKE_FIRST_FORK,philo);		// write the status
	pthread_mutex_lock(&philo->second_fork->fork); // lock second fork
	write_status(TAKE_SECOND_FORK,philo);
	//2. Eating pahse
	set_long(&philo->philo_mutex,&philo->last_meal_time, get_time(MILISECOND)); // set the time fro last meal
	philo->meal_counter++;
	write_status(EATING,philo);
	mod_usleep(philo->data->time_to_eat,philo->data);
	if (philo->data->limit_meals > 0 && philo->meal_counter == philo->data->limit_meals)
		set_bool(&philo->philo_mutex,&philo->full, true); // if eat all meals set the philo full to true
	//3. unlock the froks
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void	*philo_routine(void *data)
{
	/// wait all philo, syncro start
	//endless loop philo;

	t_philo *philo;
	philo = (t_philo *) data;
	// set time_last_meal;
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILISECOND));
	while (!simulation_finished(philo->data))
	{
		if (philo->full)
			break ;
	  	eat(philo);
		write_status(SLEEPING, philo);
		mod_usleep(philo->data->time_to_sleep, philo->data);
		thinking(philo, false);

		
	}
	return (NULL);
}


void	start_dinner(t_data *data) // problem with the index of philos or id need to check in the past
{
	int	i;

	i = -1; // -1
	if (data->limit_meals == 0)
		return ; // back to main
	else if (data->philo_nb == 1)
		pthread_create(&data->philos[0].thread_id, NULL, lone_philo, &data->philos[0]);
	else
		while (++i < data->philo_nb)
			pthread_create(&data->philos[i].thread_id,
			NULL, philo_routine, &data->philos[i]);
	// monitor thread  also call the death function
	pthread_create(&data->monitor, NULL, monitor_dinner,data);
	// start of simulation
	data->start_simulation = get_time(MILISECOND);	
	//set 's all threads ready and the mutex's  // look or unlok mutex;
	set_bool(&data->data_mutex, &data->all_threads_ready, true);
	// Wait foe everyone
	i = -1;
	while (++i < data->philo_nb )
		pthread_join(data->philos[i].thread_id,NULL);
	// if we reach this line all philos are full
	set_bool(&data->data_mutex,&data->end_simulation, true);
	pthread_join(data->monitor, NULL);
}