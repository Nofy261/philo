/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:37:21 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/23 12:47:26 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void choose_fork_order(t_philo *philo, pthread_mutex_t **first_fork, pthread_mutex_t **second_fork)
{
	if (philo->id % 2 == 0) // id pair : G puis D
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

// prend les deux fourchettes dans le bon ordre
static void take_forks(t_philo *philo, pthread_mutex_t **first_fork, pthread_mutex_t **second_fork)
{
	choose_fork_order(philo, first_fork, second_fork);
	pthread_mutex_lock(*first_fork);
	print_info(philo, "has taken a fork");
	pthread_mutex_lock(*second_fork);
	print_info(philo, "has taken a fork");	
}


// 123 1 has taken a fork : timestamp (en ld) - id du philo - message
// le philo numero 1 a pris une fourchette 123ms apres le debut du programme.


void eat(t_philo *philo)
{
	pthread_mutex_t *first_fork;
	pthread_mutex_t *second_fork;
	
	if (check_death(philo) == -1)
		return ;
	take_forks(philo, &first_fork, &second_fork);
	print_info(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);//le philo est en train de manger et ne fait rien d'autre
	
	philo->last_time_eaten = get_actual_time_in_ms();
	
	philo->meal_consumed++;
	
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	// satiete++; ??
		
}
