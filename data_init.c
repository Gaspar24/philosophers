/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:22:36 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/03 13:28:04 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nb;
	
	philo_nb = philo->data->philo_nb;
	//		position
	philo->first_fork = &forks[(philo_position + 1) % philo_nb]; 
	philo->second_fork = &forks[philo_position];
	if(philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nb]; 	
	}
	
}
	

void	philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while( ++i < data->philo_nb)
	{
		philo = data->philos + i; // pointer aritmethic it was + i;
		philo->id = i + 1; // 
		philo->full = false;
		philo->meal_counter = 0;
		philo->data = data;
		philo->dead = false;
		philo->last_meal_time = get_time(MILISECOND);
		pthread_mutex_init(&philo->philo_mutex,NULL);
		// i position in data
		assign_forks(philo, data->forks, i);
	}
}


bool	data_init(t_data *data)  // initiate all the values we 
{
	int i;
	
	i = -1;
	data->end_simulation = false;
	data->all_threads_ready = false;
	data->threads_running_nb = 0;
	data->philos = malloc(data->philo_nb * sizeof(t_philo));
	data->forks = malloc(data->philo_nb * sizeof(t_fork));
	if(!data->philos || !data->forks)
		return(printf("Memory allocation fail!\n"), false);
	pthread_mutex_init(&data->data_mutex,NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
	while (++i < data->philo_nb)
	{
		pthread_mutex_init(&data->forks[i].fork, NULL);
		data->forks->fork_id = i;
	}
	philo_init(data);
	return(true);
}

