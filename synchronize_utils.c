/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchronize_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:59:21 by msacaliu          #+#    #+#             */
/*   Updated: 2024/04/29 13:27:29 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_data *data)
{	
	// spinlock to syncronize philos starts
	while (!(get_bool(&data->data_mutex, &data->all_threads_ready)))
		;
}

// Monitor waits untill all threads running

bool 		all_threads_running(t_mtx *mutex, long *threads, long philo_nb)
{
	bool	ret;
	
	ret = false;
	pthread_mutex_lock(mutex);
	if(*threads == philo_nb)
		ret = true;
	pthread_mutex_unlock(mutex);
	return(ret);
}

//increase threads running to synchro with the monitor
void	increase_long(t_mtx *mutex, long *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}
 // try to make the system fair;
void de_syncronize_philos(t_philo *philo)
{
	if(philo->data->philo_nb % 2 == 0)
	{
		if (philo->id % 2 == 0)
			mod_usleep(3e4, philo->data);
	}
	else
	{
		if (philo->id % 2 == 1)
			thinking(philo,true);
	}
}