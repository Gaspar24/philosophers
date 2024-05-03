/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:23:07 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/03 12:15:17 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

 // get_time_of_day.  -- since midnight 1 jauary 1970
// time
// long	get_time(int time_code)
// {
//     static struct timeval	start;
//     struct timeval			now;

//     if (gettimeofday(&now, NULL))
//         printf("problem\n");
//     if (!start.tv_sec)
//         start = now;
//     if (SECOND == time_code)
//         return ((now.tv_sec - start.tv_sec) + ((now.tv_usec - start.tv_usec) / 1e6));
//     else if (MILISECOND == time_code)
//         return (((now.tv_sec - start.tv_sec) * 1e3) + ((now.tv_usec - start.tv_usec) / 1e3));
//     else if (MICROSECOND == time_code)
//         return (((now.tv_sec - start.tv_sec) * 1e6) + (now.tv_usec - start.tv_usec));
//     else
//         printf("Wrong input to get_time\n");
//     return (12345678);
// }
// precise usleep function

// void mod_usleep(long usec, t_data *data)
// {
// 	long	start;
// 	long	elapsed;
// 	long	rem;

// 	start = get_time(MICROSECOND);
// 	while (get_time(MICROSECOND) - start < usec)
// 	{
// 		if(simulation_finished(data))
// 			break ;
// 		elapsed = get_time(MICROSECOND) - start;
// 		rem = usec - elapsed;
// 		// to get spinlock
// 		if(rem > 1e4)
// 			usleep(rem / 2);
// 		// else
// 		// {
// 		// 	while (get_time(MICROSECOND) - start < usec)
// 		// 		;
			
// 		// }
// 	}
// }


long get_time(int time_code)
{
  static struct timeval start;
  static pthread_mutex_t start_mutex = PTHREAD_MUTEX_INITIALIZER;
  struct timeval now;
  (void)time_code;

  if (gettimeofday(&now, NULL) != 0)
  {
    printf("Error getting time\n");
    return -1;
  }
  pthread_mutex_lock(&start_mutex);
  if (start.tv_sec == 0 && start.tv_usec == 0)
   	 start = now;
  pthread_mutex_unlock(&start_mutex);

  return ((now.tv_sec - start.tv_sec) * 1000) + ((now.tv_usec - start.tv_usec) / 1000);
}

void mod_usleep(long msec, t_data *data)
{
  long start_time = get_time(1);
  long elapsed_time;

  while ((elapsed_time = get_time(1) - start_time) < msec) {
    if (simulation_finished(data)) {
      break;
    }
    if (msec - elapsed_time > 10) {
      usleep((msec - elapsed_time) * 500);
    }
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
	if ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		return(-1);
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			s = s * -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return(-1);
		x = x * 10 + (str[i] - '0');
		i++;
	}
	if (x > 2147483648 || (x * s) <= 0)
		return(-1);
	return (x * s);
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