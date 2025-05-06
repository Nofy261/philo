/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:42:52 by nolecler          #+#    #+#             */
/*   Updated: 2025/05/06 11:33:15 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


// est mort quand il a depassé le temps limite sans manger
int check_death(t_philo *philo)
{
	long int current_time;

	current_time = get_actual_time_in_ms();
	pthread_mutex_lock(&philo->data->death);
	if (current_time - philo->last_time_eaten >= philo->data->time_to_die)// > ??
	{
		philo->dead = 1;
		print_info(philo, "died");
		philo->data->someone_died = 1;
		pthread_mutex_unlock(&philo->data->death);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->death);
	return (0);
}

// on verifie si tous les philo ont manger suffisament le nombre de repas requis 
static int all_ate_enough(t_data *data)
{
    int i;

    if (data->nb_eat == 0)
        return (0);
    i = 0;
    while (i < data->nb_philo)
    {
        if (data->philo[i].meal_consumed < data->nb_eat)
            return (0);
        i++;
    }
    return (1); // tous ont mangé le nombre de repas requis 
}


int simulation(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->death);
		if (data->someone_died == 1)
		{
			pthread_mutex_unlock(&data->death);
			return (-1);
		}
		pthread_mutex_unlock(&data->death);
        if (all_ate_enough(data) == 1)
            return (0);
		ft_usleep(1);
	} 
	// return (0);
}





