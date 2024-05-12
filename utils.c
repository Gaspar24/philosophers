/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:23:07 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/04 14:55:57 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(int time_code)
{
	static struct timeval	start;
	static pthread_mutex_t	start_mutex = PTHREAD_MUTEX_INITIALIZER;
	struct timeval			now;

	(void) time_code;
	if (gettimeofday(&now, NULL) != 0)
	{
		printf("Error getting time\n");
		return (-1);
	}
	pthread_mutex_lock(&start_mutex);
	if (start.tv_sec == 0 && start.tv_usec == 0)
		start = now;
	pthread_mutex_unlock(&start_mutex);
	return (((now.tv_sec - start.tv_sec) * (1000))
		+ ((now.tv_usec - start.tv_usec) / 1000));
}

void	mod_usleep(long msec, t_data *data)
{
	long	start_time;
	long	elapsed_time;

	start_time = get_time(1);
	elapsed_time = start_time;
	while ((elapsed_time - start_time) < msec)
	{
		if (simulation_finished(data))
			break ;
		if (msec - (elapsed_time - start_time) > 10)
			usleep((msec - (elapsed_time - start_time)) * 500);
		elapsed_time = get_time(1);
	}
}

long	ft_atoi(char *str)
{
	long	i;
	long	x;
	int		s;

	i = 0;
	x = 0;
	s = 1;
	if ((str[0] == '0') || (str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		return (-1);
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			s = s * -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		x = x * 10 + (str[i] - '0');
		i++;
	}
	if (x > 2147483648 || (x * s) <= 0)
		return (-1);
	return (x * s);
}

// destroy the mutex;s and free the elements
void	clean(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < data->philo_nb)
	{
		philo = data->philos + i;
		pthread_mutex_destroy(&philo->philo_mutex);
	}
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->data_mutex);
	free(data->forks);
	free(data->philos);
}
