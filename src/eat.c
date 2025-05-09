/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:37:21 by nolecler          #+#    #+#             */
/*   Updated: 2025/05/09 11:10:55 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->fork_mutex);
		print_info(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->fork_mutex);
		print_info(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->fork_mutex);
		print_info(philo, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->fork_mutex);
		print_info(philo, "has taken a fork");
	}
}


int 	philo_eat(t_philo *philo)
{
	long int	tmp;
	
	if (check_death(philo) == -1)
		return (0);
	take_forks(philo);
	if (check_death(philo) == -1)
    {
		pthread_mutex_unlock(&philo->left_fork->fork_mutex);
		pthread_mutex_unlock(&philo->right_fork->fork_mutex);
		return (0);
    }
	print_info(philo, "is eating");
	tmp = get_actual_time_in_ms();
	while (get_actual_time_in_ms() - tmp < philo->data->time_to_eat)
	{
		if (check_death(philo) == -1)
		{
			pthread_mutex_unlock(&philo->left_fork->fork_mutex);
			pthread_mutex_unlock(&philo->right_fork->fork_mutex);
			return (0);
		}
		usleep(100);
	}
	pthread_mutex_lock(&philo->time_mutex);
	philo->last_time_eaten = get_actual_time_in_ms();
	pthread_mutex_unlock(&philo->time_mutex);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meal_consumed++;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
	return (1);
}

