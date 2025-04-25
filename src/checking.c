/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:42:52 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/25 11:11:38 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


// a mettre dans fichier checking
// est mort quand il a depassé le temps limite sans manger
int check_death(t_philo *philo) // a completer plus tard
{
	long int current_time;

	current_time = get_actual_time_in_ms();
	pthread_mutex_lock(&philo->data->death);
	if (current_time - philo->last_time_eaten > philo->data->time_to_die)
	{
		philo->data->someone_died = 1;
		
		pthread_mutex_lock(&philo->data->death); // a voir 
		philo->dead = 1;  // Marque le philosophe comme mort
		print_info(philo, "died");
		pthread_mutex_unlock(&philo->data->death);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->death);
	return (0);
}


int simulation(t_data *data)
{
	int i;

	while (1)
	{
		pthread_mutex_lock(&data->death);
		if (data->someone_died == 1)
		{
			pthread_mutex_unlock(&data->death);
			return (-1);
		}
		i = 0;
		while(i < data->nb_philo)
		{
			if(check_death(&data->philo[i]) == -1)
				return (-1);
			i++;
		}
		// ft_usleep(100)?? a testet avec plusieurs valeurs
	}
	// a rajouter si nb_eat est atteint
	// si tout le monde a mangé le nombre de repas requis  
	return (0);
}





