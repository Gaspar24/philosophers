/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:01:25 by msacaliu          #+#    #+#             */
/*   Updated: 2024/04/11 15:05:56 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return(i);
}

long ft_atoi(char *str)//need to check for nb > INT_MAX
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	if (str[0] == '-')
		return (-1);
	if (str[0] == '+')
		i++;
	while (str[i])
	{
		while(str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] >= '0' && str[i] <= '9')
			nb = nb * 10 + (str[i] - '0');
		else
			return(-1);
		i++;
	}
	return (nb);
}

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}


void	slp_pause(long long msec)
{
	long long	now;
	long long	elapsed;

	now = get_time();
	elapsed = get_time();
	while (elapsed - now < msec)
	{
		usleep(100);
		elapsed = get_time();
	}
}