/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:18:06 by msacaliu          #+#    #+#             */
/*   Updated: 2024/04/24 14:49:59 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// to do 
	// 1 philo
	// int max and min
	// input validations
	// philo is not dying
	// and more+


int	main(int argc, char *argv[])
{
	t_data data;
	
	if (argc < 5 || argc > 6)
		return(printf("Wrong number of arguments!\n"),1);

	if(validate_input(&data, argv, argc) == false) // nedd int min and max
		return(printf("Invalid input\n"),1);
	data_init(&data);
	start_dinner(&data);
	// clean(&data);
	
	return (0);
}