/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:38:30 by msacaliu          #+#    #+#             */
/*   Updated: 2024/04/26 16:42:01 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool philo_died(t_philo *philo)
{
	long	elapsed;
	long time_to_die;	
	
	// check maybe just finished his own simulation or full
	if(get_bool(&philo->philo_mutex, &philo->full))
		return (false);
								// lock the philo
	elapsed = get_time(MILISECOND) - get_long(&philo->philo_mutex,&philo->last_meal_time);
	time_to_die = philo->data->time_to_die / 1e3;

	if(elapsed > time_to_die)
		return(true);
	return(false);
}

void	*monitor_dinner(void *data) // ned to change the name of the parameter
{									// so i can use data no data 1 (TO DO)
	int	i;
	t_data *data1;
	data1 = (t_data *)data;

	//make sure all philos are running
	// spinlock till all threads run
	while (!all_threads_running(&data1->data_mutex, &data1->threads_running_nb, data1->philo_nb)) 
		;
	//
	while (!simulation_finished(data1))
	{
		i = -1;
		while (++i <data1->philo_nb && !simulation_finished(data1))
		{
			if(philo_died(data1->philos + i)) // pointer aritmethic
			{
				set_bool(&data1->data_mutex, &data1->end_simulation,true);
				write_status(DIED, data1->philos + i);
			}
		}
		
	}
	
	return(NULL);
}