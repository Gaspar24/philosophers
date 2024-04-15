/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:48:27 by msacaliu          #+#    #+#             */
/*   Updated: 2024/04/15 18:08:39 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*philo_routine(void *data)
{
	/// wait all philo, syncro start
	//endless loop philo;
	
	t_philo *philo;
	philo = (t_philo *) data;

	wait_all_threads(philo->data ); //to do


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
			pthread_create(&data->philos[i].thread_id, NULL, &philo_routine, NULL);
			i++;
		}
	/// also join
		
		
}