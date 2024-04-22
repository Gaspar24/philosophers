/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:23:07 by msacaliu          #+#    #+#             */
/*   Updated: 2024/04/22 12:53:02 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

 // get_time_of_day.  -- since midnight 1 jauary 1970
// time
long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
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
	long long	now;
	long long	elapsed;

	now = get_time();
	elapsed = get_time();
	while (elapsed - now < usec)
	{
		if (simulation_finished(data))
			break ;
		usleep(100);
		elapsed = get_time();
	}
}