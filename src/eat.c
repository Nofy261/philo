/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:37:21 by nolecler          #+#    #+#             */
/*   Updated: 2025/05/08 12:29:03 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_left);
		print_info(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_right);
	}
	else
	{
		pthread_mutex_lock(philo->fork_right);
		print_info(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_left);
	}
	print_info(philo, "has taken a fork");
}

static void put_down_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
	}
	else
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
	}
}

void 	philo_eat(t_philo *philo)
//int	philo_eat(t_philo *philo)
{
	long int	tmp;
	
	if (check_death(philo) == -1)
		//return (-1);
		return ;
	take_forks(philo);
	print_info(philo, "is eating");
	tmp = get_actual_time_in_ms();
	while (get_actual_time_in_ms() - tmp < philo->data->time_to_eat)
	{
		if (check_death(philo) == -1)
		{
			put_down_forks(philo);
			//return (-1) ;
			return ;
		}
		usleep(100);
	}
	pthread_mutex_lock(&philo->time_mutex);
	philo->last_time_eaten = get_actual_time_in_ms();
	pthread_mutex_unlock(&philo->time_mutex);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meal_consumed++;
	pthread_mutex_unlock(&philo->meal_mutex);
	put_down_forks(philo);
	//return (0);
}

