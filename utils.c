/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:23:07 by msacaliu          #+#    #+#             */
/*   Updated: 2024/04/29 12:34:07 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

 // get_time_of_day.  -- since midnight 1 jauary 1970
// time
long	get_time(t_time_code time_code)
{
	struct timeval	tv;

	if(gettimeofday(&tv, NULL))
		printf("problem\n");
	if (SECOND == time_code)
		return(tv.tv_sec + (tv.tv_usec /1e6));
	else if (MILISECOND == time_code)
		return((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if(MICROSECOND == time_code)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		printf("Wrong input to get_rime\n");
	return(12345678);
	
}

long	ft_atoi(char *str)
{
	long	rez;
	int		i;

	rez = 0;
	i = 0;
	if (str[0] == '-')
		return (-1);
	else if (str[i] == '+')
		i++;
	while(str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			rez = rez * 10 + (str[i] - '0');
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		i++;
	}
	return (rez);
}

// precise usleep function

void mod_usleep(long usec, t_data *data)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if(simulation_finished(data))
			break ;
		elapsed = get_time(MICROSECOND) - start;
		rem = usec - elapsed;
		// to get spinlock
		if(rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (get_time(MICROSECOND) - start < usec)
				;
			
		}
	}
}
// destroy the mutex;s and free the elements
void	clean(t_data *data)
{
	t_philo *philo;
	int	i;

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