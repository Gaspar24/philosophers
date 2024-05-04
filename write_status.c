/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:41:52 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/03 13:57:51 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
	// Function to write the philo status
void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = get_time(MILISECOND);
	if (philo->full)
		return ;
	pthread_mutex_lock(&philo->data->write_mutex);
	if ((!simulation_finished(philo->data))
		&& (TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status))
		printf("%ld  %d has taken a fork\n", elapsed, philo->id);
	else if (EATING == status && !simulation_finished(philo->data))
		printf("%ld  %d is eating\n", elapsed, philo->id);
	else if (SLEEPING == status && !simulation_finished(philo->data))
		printf("%ld  %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status && !simulation_finished(philo->data))
		printf("%ld  %d is THINKING\n", elapsed, philo->id);
	else if (DIED == status && simulation_finished(philo->data))
		printf("%ld  %d is dead\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->data->write_mutex);
}
