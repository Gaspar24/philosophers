/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchronize_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:59:21 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/04 14:50:11 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_nb == 1)
		lone_philo(philo);
	if (philo->id % 2 == 0)
		write_status(THINKING, philo);
	philo_routine(philo);
	return (NULL);
}
