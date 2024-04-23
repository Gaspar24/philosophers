/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchronize_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:59:21 by msacaliu          #+#    #+#             */
/*   Updated: 2024/04/23 17:44:27 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_data *data)
{	
	// spinlock to syncronize philos starts
	printf("test syncrone\n");
	while (!(get_bool(&data->data_mutex, &data->all_threads_ready)))
		;
	
}

