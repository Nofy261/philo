/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:43:21 by nolecler          #+#    #+#             */
/*   Updated: 2025/05/08 08:48:58 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// void print_info_2(t_philo *philo, char *msg)
// {
// 	long	time;

// 	time = get_timestamp(philo->data);
// 	pthread_mutex_lock(&philo->data->print);
// 	printf("%ld %d %s\n", time, philo->id, msg);
// 	pthread_mutex_unlock(&philo->data->print);
// }

void print_info(t_philo *philo, char *msg)
{
	long	time;

	time = get_timestamp(philo->data);
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->death);
	if (!philo->data->someone_died) // == 0
		printf("%ld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->death);
	pthread_mutex_unlock(&philo->data->print);
}

void cleanup(t_data *data)
{
	int i;
	
	i = 0;
	while (i < data->nb_philo)
    {
		if (data->philo[i].has_thread == 1)
        	pthread_join(data->philo[i].thread, NULL);
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].meal_mutex);
		pthread_mutex_destroy(&data->philo[i].time_mutex);
        i++;
    }
	pthread_mutex_destroy(&data->print);
    pthread_mutex_destroy(&data->death);
}
