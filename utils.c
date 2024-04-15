/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:23:07 by msacaliu          #+#    #+#             */
/*   Updated: 2024/04/15 15:17:50 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


long	ft_atoi(char *str)
{
	long	rez;
	int		i;

	rez = 0;
	i = 0;
	if (str[0] == '-')
		return (-1);
	else if (str[i] == '+')
		i++;
	while(str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			rez = rez * 10 + (str[i] - '0');
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		i++;
	}
	return (rez);
}