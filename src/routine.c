/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:13:41 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/25 13:36:19 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


void *routine(void *arg)
{
    t_philo *philo;
	
	philo = (t_philo *)arg;
	if (philo->data->nb_philo == 1)
    {
        pthread_mutex_lock(&philo->fork_right);
        print_info(philo, "has taken a fork");
        ft_usleep(philo->data->time_to_die);
        print_info(philo, "died");
        pthread_mutex_unlock(&philo->fork_right);

        pthread_mutex_lock(&philo->data->death);
        philo->data->someone_died = 1;
        pthread_mutex_unlock(&philo->data->death);
        return (NULL);
    }
    while (1)
    {
        pthread_mutex_lock(&philo->data->death);
        if (philo->data->someone_died == 1)
        {
            pthread_mutex_unlock(&philo->data->death);
            break;
        }
        pthread_mutex_unlock(&philo->data->death);
        if (philo->data->nb_eat != 0 && philo->meal_consumed >= philo->data->nb_eat)
            break;
        eat(philo);
        pthread_mutex_lock(&philo->data->death);
        if (philo->data->someone_died == 1)
        {
            pthread_mutex_unlock(&philo->data->death);
            break;
        }
        pthread_mutex_unlock(&philo->data->death);
        print_info(philo, "is sleeping");
        ft_usleep(philo->data->time_to_sleep);
        print_info(philo, "is thinking");
    }
    return (NULL);
}
