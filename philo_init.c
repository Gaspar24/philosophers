/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:22:36 by msacaliu          #+#    #+#             */
/*   Updated: 2024/04/12 15:30:14 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philosophers_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
        if (philo->eating == 0)
        {
            printf("%llu %d is eating\n", get_time() - philo->start, philo->id);
            philo->eating = 1;
            philo->last_meal = get_time();
            usleep(philo->eat_timer);
            philo->eating = 0;
            philo->total_meals++;
        }
        if (philo->sleeping == 0)
        {
            printf("%llu %d is sleeping\n", get_time() - philo->start, philo->id);
            philo->sleeping = 1;
            usleep(philo->slp_timer);
            philo->sleeping = 0;
        }
        if (philo->thinking == 0)
        {
            printf("%llu %d is thinking\n", get_time() - philo->start, philo->id);
            philo->thinking = 1;
        }
		if (get_time() - philo->last_meal > philo->die_timer)
        {
            printf("%llu %d has died\n", get_time() - philo->start, philo->id);
            philo->dead = 1;
            exit(1);
        }
    }
    return (NULL);
}



void	init_philo_values(t_philo *philo, int index)
{
	philo->id = index + 1;
	philo->dead = 0;
	philo->eating = 0;
	philo->dead = 0;
	philo->thinking = 0;
	philo->total_meals = 0;
}

t_philo *create_philosophers(int num_philos)
{
    int i;
    t_philo *philos;

    philos = malloc(num_philos * sizeof(t_philo));
    if (philos == NULL)
    {
        printf("Error: Could not allocate philosophers!\n");
        return (NULL);
    }
    i = 0;
    while (i < num_philos)
    {
        init_philo_values(philos + i, i);
        if(pthread_create(&(philos[i].thread), NULL, &philosophers_routine, &philos[i]) != 0)
        {
            printf("Error: Could not create thread %d!\n", i);
            free(philos);
            return (NULL);
        }
        i++;
    }

    for (i = 0; i < num_philos; i++)
    {
        pthread_join(philos[i].thread, NULL);
    }
	return(NULL);
}