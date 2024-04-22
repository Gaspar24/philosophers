/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:48:27 by msacaliu          #+#    #+#             */
/*   Updated: 2024/04/22 14:13:01 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

	// eat routine

	// 1. grab the forks;
	// 2.eating : write eat, update last meal, update meals counter, bool full if needed
	// realease the forks

static void eat(t_philo *philo)
{
	//1.
	pthread_mutex_lock(&philo->first_fork->fork);
	write_status(TAKE_FIRST_FORK,philo);
	pthread_mutex_unlock(&philo->first_fork->fork);
	write_status(TAKE_SECOND_FORK,philo);
	//2.
	// set_long()
}


void	*philo_routine(void *data)
{
	/// wait all philo, syncro start
	//endless loop philo;
	
	t_philo *philo;
	philo = (t_philo *) data;
	//spin lock  // unitill all flags are set to true
	wait_all_threads(philo->data ); // every philo will wait for the treads to be ready

	// set last_meal_time

	while (!simulation_finished(philo->data))
	{
		// 1) am i full?
		if(philo->full) // to do;
			break ;
		//2) eat
		eat(philo); // to do;
		
		//3)sleep ->write_status && precise usleep
		write_status(SLEEPING, philo);
		mod_usleep(philo->data->time_to_sleep, philo->data);
		
		// 4) think
		thinking(philo);
	}
	

	return (NULL);
}

void	start_dinner(t_data *data)
{
	int i;

	i = 0;
	if (data->limit_meals == 0)
		return ; // back to main
	else if (data->philo_nb = 1)
		;// to do
	else
		while (i < data->philo_nb)
		{
			pthread_create(&data->philos[i].thread_id, NULL, philo_routine, &data->philos[i]); // need a check
			i++;
		}
	
	/// also join (i think :))   -) to do
	
	// start of simulation
	data->start_simulation = get_time();
	
	//set 's all threads ready and the mutex's  // look or unlok mutex;
	set_bool(&data->data_mutex, &data->all_threads_ready, true);
	
	// Wait foe everyone
	i = 0;
	while (i < data->philo_nb )
	{
		pthread_join(&data->philos[i],NULL);
		i++;
	}

	// if we reach this line all philos are full
	
	
		
}