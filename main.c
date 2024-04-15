/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:18:06 by msacaliu          #+#    #+#             */
/*   Updated: 2024/04/15 15:19:47 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data data;
	
	if (argc < 5 || argc > 6)
		return(printf("Wrong number of arguments!\n"),1);

	if(validate_input(&data, argv, argc) == false) // nedd int min and max
		return(printf("Invalid input\n"),1);
	// printf("%ld\n", data.philo_nb);
	// printf("%ld\n", data.time_to_die);
	// printf("%ld\n", data.time_to_eat);
	// printf("%ld\n", data.time_to_sleep);
	// printf("%ld\n", data.limit_meals);

	// data_init(&data);
	// dinner_start(&data);
	// clean(&data);
	
	return (0);
}