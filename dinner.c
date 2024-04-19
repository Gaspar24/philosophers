/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:48:27 by msacaliu          #+#    #+#             */
/*   Updated: 2024/04/19 15:02:13 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*philo_routine(void *data)
{
	/// wait all philo, syncro start
	//endless loop philo;
	
	t_philo *philo;
	philo = (t_philo *) data;
	//spin lock  // unitill all flags are set to true
	wait_all_threads(philo->data ); // every philo will wait for the treads to be ready


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
	
	
	//set 's all threads ready and the mutex's  // look or unlok mutex;
	set_bool(&data->data_mutex, &data->all_threads_ready, true);
	
		
}