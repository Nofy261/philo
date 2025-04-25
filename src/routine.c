/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:13:41 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/25 10:54:41 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//void	routine(t_philo *philo)
void *routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	if (philo->data->nb_eat > 0)
	{ 
		while (philo->meal_consumed < philo->data->nb_eat) // mais c est facultatif
		{
			if (check_death(philo) == -1)
				break ;
			eat(philo);
			print_info(philo, "is sleeping");
			ft_usleep(philo->data->time_to_sleep);
			print_info(philo, "is thinking");// a voir si ne pose pas de probleme
		}
	}
	while (1)
	{
		if (check_death(philo) == -1)
				break ;
			eat(philo);
			print_info(philo, "is sleeping");
			ft_usleep(philo->data->time_to_sleep);
			print_info(philo, "is thinking");
		
	}
	return (NULL);
}
