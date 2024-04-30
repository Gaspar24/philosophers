/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:27:25 by msacaliu          #+#    #+#             */
/*   Updated: 2024/04/30 13:27:03 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


bool	validate_input(t_data *data, char *argv[], int argc)
{
	if ((data->philo_nb = ft_atoi(argv[1])) == -1)
		return(false);
	if ((data->time_to_die = ft_atoi(argv[2])) == -1)
		return( false);
	if ((data->time_to_eat = ft_atoi(argv[3])) == -1)
		return( false);
	if ((data->time_to_sleep = ft_atoi(argv[4])) == -1)
		return(false);
	if(argc == 6)
	{
		if ((data->limit_meals = ft_atoi(argv[5])) == -1)
			return(false);
	}
	else
		data->limit_meals = INT_MAX;
	data->time_to_die *= 1e3;
	data->time_to_eat *= 1e3;
	data->time_to_sleep *= 1e3;
	return(true);
}