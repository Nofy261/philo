/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:13:41 by nolecler          #+#    #+#             */
/*   Updated: 2025/05/06 11:52:25 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// ./philo 5 800 200 200 7
// quand les philos ont atteint le nombre de repas requis , il continue leur routine manger dormir penser et fini par mourir...
// le mien ne reprend pas sa routine et ne finit pas par mourir

static void philos_life(t_philo *philo)
{
	long int	tmp;

	while (1)
    {
        pthread_mutex_lock(&philo->data->death);
        if (philo->data->someone_died == 1)
        {
            pthread_mutex_unlock(&philo->data->death);
            return ;
        }
        pthread_mutex_unlock(&philo->data->death);
        if (philo->data->nb_eat != 0 && philo->meal_consumed >= philo->data->nb_eat)
        //{
			// si le temps de mort est depassé
			//if (get_actual_time_in_ms() == philo->data->time_to_die)
				return ;// tous ont mangé le nombre de repas requis
		//}
        eat(philo);
        pthread_mutex_lock(&philo->data->death);
        if (philo->data->someone_died == 1)
        {
            pthread_mutex_unlock(&philo->data->death);
            return ;
        }
        pthread_mutex_unlock(&philo->data->death);
        print_info(philo, "is sleeping");
		tmp = get_actual_time_in_ms();
		while (get_actual_time_in_ms() - tmp < philo->data->time_to_sleep)
		{
			if (check_death(philo) == -1)
				return ;
			usleep(100);
		}
        print_info(philo, "is thinking");
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
        ft_usleep(philo->data->time_to_die);
		//usleep(philo->data->time_to_die * 1000); // modif
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


