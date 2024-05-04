/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:27:25 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/04 15:26:27 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	validate_input(t_data *data, char *argv[], int argc)
{
	data->philo_nb = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->limit_meals = ft_atoi(argv[5]);
	else
		data->limit_meals = INT_MAX;
	if (data->philo_nb == -1)
		return (false);
	if (data->time_to_die == -1)
		return (false);
	if (data->time_to_eat == -1)
		return (false);
	if (data->time_to_sleep == -1)
		return (false);
	if (argc == 6)
		if (data->limit_meals == -1)
			return (false);
	return (true);
}
