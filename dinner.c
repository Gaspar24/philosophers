/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:48:27 by msacaliu          #+#    #+#             */
/*   Updated: 2024/04/26 16:46:08 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

	//Death Routine static
// static void	death(t_philo *philo)
// {
// 	long current_time;
// 	current_time = get_time(MILISECOND);
// 	printf("philo->last_meal_time :%ld\n",philo->last_meal_time);
// 	long	time_since_last_meal =(current_time - philo->last_meal_time);
// 	printf("time since last meal :%ld for philo nr :%d\n", time_since_last_meal, philo->id);
// 	printf("time to die : %ld\n",(philo->data->time_to_die));
// 	philo->data->time_to_die /= 1e3;
// 	if (time_since_last_meal > (philo->data->time_to_die)) //  (/1e3)
// 	{
// 		philo->dead = true;
// 		printf("%ld %d died\n", get_time(MILISECOND) - philo->data->start_simulation, philo->id);
// 	}
// } 


	//same algo but..
	// 1)fake to lock the fork
	// 2) sleep until the monitor will bust it
	
	void	*lone_philo(void *arg)
	{
		t_philo *philo;
		philo = (t_philo *)arg;
		
		wait_all_threads(philo->data);
		set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILISECOND));
		increase_long(&philo->data->data_mutex, &philo->data->threads_running_nb);
		write_status(TAKE_FIRST_FORK, philo);
		// write_status(DIED,philo);
		while (!simulation_finished(philo->data))
		{
			usleep(200);
		}
		return(NULL);
	}


	// THINKING routine  
static	void thinking(t_philo *philo) //TODO
{
	write_status(THINKING,philo);
}



	// EAT routine
		// 1. grab the forks;
		// 2.eating : write eat, update last meal, update meals counter, bool full if needed
		// 3.realease the forks
static void eat(t_philo *philo) 
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
	//spin lock  // unitill all flags are set to true
	wait_all_threads(philo->data ); // every philo will wait for the treads to be ready
	
	// set time_last_meal;
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILISECOND));
	
	// syncro with monitor
	// incrise a table variable with all threads running
	increase_long(&philo->data->data_mutex, &philo->data->threads_running_nb);
	
	// set last_meal_time
	while (!simulation_finished(philo->data))
	{
		// 1) am i full?
		if(philo->full)
		{
			// printf("philo nr : %d is full\n", philo->id);
			break ;
		} // to do;
		//2) eat
		eat(philo); // done
		//3)sleep ->write_status && precise usleep
		write_status(SLEEPING, philo);
		mod_usleep(philo->data->time_to_sleep, philo->data);
		// 4) think
		thinking(philo);
		 // 5) die
		// death(philo);
		// if(philo->dead == true)
		// {
		// 	printf("philo nr: %d died\n",philo->id);
		// 	exit(1);
			
		// } 
	}
	
	return (NULL);
}

void	start_dinner(t_data *data) // problem with the index of philos or id need to check in the past
{
	int i;

	i = -1; // -1
	if (data->limit_meals == 0)
		return ; // back to main
	else if (data->philo_nb == 1)
		pthread_create(&data->philos[0].thread_id, NULL, lone_philo, &data->philos[0]);
	else
	while (++i < data->philo_nb)
		pthread_create(&data->philos[i].thread_id, NULL, philo_routine, &data->philos[i]); // need a check
	// monitor thread
	pthread_create(&data->monitor, NULL, monitor_dinner,data);  //to do
	
	// start of simulation
	data->start_simulation = get_time(MILISECOND);
	
	//set 's all threads ready and the mutex's  // look or unlok mutex;
	set_bool(&data->data_mutex, &data->all_threads_ready, true);
	
	// Wait foe everyone
	i = 0;
	while (i < data->philo_nb )
	{
		pthread_join(data->philos[i].thread_id,NULL);
		i++;
	}

	// if we reach this line all philos are full
	
	
}