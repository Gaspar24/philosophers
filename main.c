/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:18:06 by msacaliu          #+#    #+#             */
/*   Updated: 2024/04/12 13:36:48 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void *routine(pthread_t *philos)
// {
// 	printf("philo is eating\n");
// }


int	main(int argc, char *argv[])
{
	int i;
	
	i = 0;
	t_philo philo;
	t_philo *philos = NULL;
	if(argc < 5 || argc > 6)
		return(printf("Wrong number of arguments\n"),1);
	if(!check_args(argc, argv, &philo))
		return(printf("wrong input\n"),1);
	philos = create_philosophers(philo.ph_num);

	
	
	return (0);
}