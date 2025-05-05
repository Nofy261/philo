/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:37:21 by nolecler          #+#    #+#             */
/*   Updated: 2025/05/05 13:28:05 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_right);
		print_info(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_left);
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		print_info(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_right);
	}
	print_info(philo, "has taken a fork");
}

static void put_down_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
	}
	else
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
	}
}

void	eat(t_philo *philo)
{
	if (check_death(philo) == -1)
		return ;
	take_forks(philo);
	print_info(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	philo->last_time_eaten = get_actual_time_in_ms();
	// ft_usleep(philo->data->time_to_eat);
	philo->meal_consumed++;
	put_down_forks(philo);
	// satiete++; ??
}
