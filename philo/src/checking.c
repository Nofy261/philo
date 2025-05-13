/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:42:52 by nolecler          #+#    #+#             */
/*   Updated: 2025/05/13 08:27:31 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	create_threads(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].has_thread = 0;
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
		{
			print_error("Error: thread creation failed");
			cleanup(data);
			return (-1);
		}
		philo[i].has_thread = 1;
		i++;
	}
	return (0);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->stop_sim == 1)
	{
		pthread_mutex_unlock(&philo->data->death);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->death);
	pthread_mutex_lock(&philo->time_mutex);
	if (get_actual_time_in_ms()
		- philo->last_time_eaten >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->death);
		if (philo->data->stop_sim == 1)
		{
			pthread_mutex_unlock(&philo->data->death);
			return (-1);
		}
		philo->data->stop_sim = 1;
		pthread_mutex_unlock(&philo->data->death);
		pthread_mutex_unlock(&philo->time_mutex);
		print_death(philo, "died");
		return (-1);
	}
	pthread_mutex_unlock(&philo->time_mutex);
	return (0);
}

static int	all_ate_enough(t_data *data)
{
	int	i;

	if (data->nb_eat == 0)
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->philo[i].meal_mutex);
		if (data->philo[i].meal_consumed < data->nb_eat)
		{
			pthread_mutex_unlock(&data->philo[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->philo[i].meal_mutex);
		i++;
	}
	return (1);
}

int	simulation(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->death);
		if (data->stop_sim == 1)
		{
			pthread_mutex_unlock(&data->death);
			return (-1);
		}
		pthread_mutex_unlock(&data->death);
		if (all_ate_enough(data) == 1)
		{
			pthread_mutex_lock(&data->death);
			data->stop_sim = 1;
			pthread_mutex_unlock(&data->death);
		}
		usleep(1);
		//usleep(500);
	}
}
