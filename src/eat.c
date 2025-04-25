/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:37:21 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/25 14:18:49 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	choose_fork_order(t_philo *philo, pthread_mutex_t **first_fork,
		pthread_mutex_t **second_fork)
{
	if (philo->id % 2 == 0)
	{
		*first_fork = &philo->fork_left;
		*second_fork = &philo->fork_right;
	}
	else
	{
		*first_fork = &philo->fork_right;
		*second_fork = &philo->fork_left;
	}
}

static int	take_forks(t_philo *philo, pthread_mutex_t **first_fork,
		pthread_mutex_t **second_fork)
{
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
		return (-1);
	}
	choose_fork_order(philo, first_fork, second_fork);
	pthread_mutex_lock(*first_fork);
	print_info(philo, "has taken a fork");
	pthread_mutex_lock(*second_fork);
	print_info(philo, "has taken a fork");
	return (0);
}

// 123 1 has taken a fork : timestamp (en ld) - id du philo - message
// le philo numero 1 a pris une fourchette 123ms apres le debut du programme.

void	eat(t_philo *philo)
{
	pthread_mutex_t *first_fork;
	pthread_mutex_t *second_fork;

	if (check_death(philo) == -1)
		return ;
	if (take_forks(philo, &first_fork, &second_fork) == -1)
		return ;
	print_info(philo, "is eating");
	philo->last_time_eaten = get_actual_time_in_ms();
	ft_usleep(philo->data->time_to_eat);
	philo->meal_consumed++;
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	// satiete++; ??
}
