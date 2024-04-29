/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:18:06 by msacaliu          #+#    #+#             */
/*   Updated: 2024/04/29 12:25:47 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// dies on 4 310 200 100

// to do 
	// 1 philo
	// int max and min
	// input validations
	// philo is not dying
	// and more+

// long	get_time1(void)
// {
// 	struct timeval	t;

// 	gettimeofday(&t, NULL);
// 	return ((t.tv_sec * 1e3) + (t.tv_usec / 1e3));
// }

int	main(int argc, char *argv[])
{
	t_data data;
	
	if (argc < 5 || argc > 6)
		return(printf("Wrong number of arguments!\n"),1);

	if(validate_input(&data, argv, argc) == false) // nedd int min and max
		return(printf("Invalid input\n"),1);

	data_init(&data);		
	start_dinner(&data);
	clean(&data);
	
	return (0);
}