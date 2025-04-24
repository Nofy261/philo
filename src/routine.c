/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:13:41 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/24 16:04:25 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(t_philo *philo)
{
	// tant qu'aucun philo est mort ou
	// tant que tous les philos n'ont pas manger le nombre de repas demandés 
	while (philo->data->nb_eat == 0 || philo->meal_consumed < philo->data->nb_eat) // mais c est facultatif
	{
		if (check_death(philo) == -1)
			break ;
		eat(philo);
		print_info(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		print_info(philo, "is thinking");// a voir si ne pose pas de probleme
	}
}

