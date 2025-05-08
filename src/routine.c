/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:13:41 by nolecler          #+#    #+#             */
/*   Updated: 2025/05/08 12:01:34 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int philo_sleep_and_think(t_philo *philo)
{
	long int tmp;
	
	print_info(philo, "is sleeping");
	tmp = get_actual_time_in_ms();
	// get_actual_time_in_ms() - tmp = temps qui s'est ecoulé depuis le debut de sommeil
	while (get_actual_time_in_ms() - tmp < philo->data->time_to_sleep) // tant que time_to_sleep n'est pas atteint, on attend
	{
		if (check_death(philo) == -1)
			return (-1);
		usleep(100);
	}
	print_info(philo, "is thinking");
	return (0);
}
 
static void philos_life(t_philo *philo)
{
	while (1)
    {
		pthread_mutex_lock(&philo->data->death);
		if (philo->data->someone_died == 1)	
		{
			pthread_mutex_unlock(&philo->data->death);
			return ;
		}
		pthread_mutex_unlock(&philo->data->death);
		pthread_mutex_lock(&philo->meal_mutex);
        if (philo->data->nb_eat != 0 && philo->meal_consumed >= philo->data->nb_eat)
		{
			pthread_mutex_unlock(&philo->meal_mutex);
			return ;// tous ont mangé le nombre de repas requis
		}
		pthread_mutex_unlock(&philo->meal_mutex); 
        if (philo_eat(philo) == -1)
			return ;
        pthread_mutex_lock(&philo->data->death);
        if (philo->data->someone_died == 1)
        {
            pthread_mutex_unlock(&philo->data->death);
            return ;
        }
        pthread_mutex_unlock(&philo->data->death);
		if (philo_sleep_and_think(philo) == -1)
			return ;
    }
}

void *routine(void *arg)
{
    t_philo *philo;
	
	philo = (t_philo *)arg;
	if (philo->data->nb_philo == 1)
    {
        pthread_mutex_lock(philo->fork_right);
        print_info(philo, "has taken a fork");
        //ft_usleep(philo->data->time_to_die);
		usleep(philo->data->time_to_die * 1000); // modif
        print_info(philo, "died");
        pthread_mutex_unlock(philo->fork_right);
        pthread_mutex_lock(&philo->data->death);
        philo->data->someone_died = 1;
        pthread_mutex_unlock(&philo->data->death);
    }
	else
		philos_life(philo);
	return (NULL);
}


