/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:38:30 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/03 13:56:08 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;	

	// check maybe just finished his own simulation or full
	if(get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = get_time(MILISECOND) - get_long(&philo->philo_mutex, &philo->last_meal_time);
	time_to_die = philo->data->time_to_die - 1;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_data	*table;

	table = (t_data *)data;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nb && !simulation_finished(table))
		{
			// pointer aritmethic
			if (philo_died(table->philos + i)) 
			{
				set_bool(&table->data_mutex, &table->end_simulation,true);
				write_status(DIED, table->philos + i);
			}
		}
	}
	return (NULL);
}