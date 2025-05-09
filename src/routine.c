/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:13:41 by nolecler          #+#    #+#             */
/*   Updated: 2025/05/09 13:38:25 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	philo_sleep_and_think(t_philo *philo)
{
	long int	tmp;

	print_info(philo, "is sleeping");
	tmp = get_actual_time_in_ms();
	while (get_actual_time_in_ms() - tmp < philo->data->time_to_sleep)
	{
		if (check_death(philo) == -1)
			return (-1);
		usleep(100);
	}
	print_info(philo, "is thinking");
	return (0);
}

static int	should_stop_sim(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->stop_sim == 1)
	{
		pthread_mutex_unlock(&philo->data->death);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death);
	return (1);
}

static void	philos_life(t_philo *philo)
{
	while (1)
	{
		if (should_stop_sim(philo) == 0)
			return ;
		pthread_mutex_lock(&philo->meal_mutex);
		if (philo->data->nb_eat != 0
			&& philo->meal_consumed >= philo->data->nb_eat)
		{
			pthread_mutex_unlock(&philo->meal_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->meal_mutex);
		if (!philo_eat(philo))
			return ;
		if (should_stop_sim(philo) == 0)
			return ;
		if (philo_sleep_and_think(philo) == -1)
			return ;
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_lock(&philo->right_fork->fork_mutex);
		print_info(philo, "has taken a fork");
		usleep(philo->data->time_to_die * 1000);
		print_info(philo, "died");
		pthread_mutex_unlock(&philo->right_fork->fork_mutex);
		pthread_mutex_lock(&philo->data->death);
		philo->data->stop_sim = 1;
		pthread_mutex_unlock(&philo->data->death);
	}
	else
		philos_life(philo);
	return (NULL);
}
