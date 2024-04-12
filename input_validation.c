/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:17:10 by msacaliu          #+#    #+#             */
/*   Updated: 2024/04/12 12:14:49 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int check_args(int argc, char *argv[], t_philo *philo)
{
	if ((philo->ph_num = ft_atoi(argv[1])) == -1)
		return(0);
	if ((philo->die_timer= ft_atoi(argv[2])) == -1)
		return(0);
	if ((philo->eat_timer = ft_atoi(argv[3])) == -1)
		return(0);
	if ((philo->slp_timer = ft_atoi(argv[4])) == -1)
		return(0);
	if(argc == 6 )
		if ((philo->total_meals = ft_atoi(argv[5])) == -1)
			return(0);
	philo->die_timer *= 1e3;
	philo->eat_timer *= 1e3;
	philo->slp_timer *= 1e3;
	return(1);
}