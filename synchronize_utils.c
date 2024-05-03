/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchronize_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:59:21 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/03 13:55:30 by msacaliu         ###   ########.fr       */
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

bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nb)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(mutex);
	if (*threads == philo_nb)
		ret = true;
	pthread_mutex_unlock(mutex);
	return (ret);
}
