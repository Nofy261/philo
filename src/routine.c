/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:37:21 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/17 13:45:18 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// a mettre dans fichier checking
int check_death(t_philo *philo)
{
	if (philo->dead == 1)
	{
		ft_putstr_fd("philo is dead", 2);// ou printf
		return (-1);
	}
	return (0);
}

// a mettre dans checking
void choose_fork_order(t_philo *philo, pthread_mutex_t **first_fork, pthread_mutex_t **second_fork)
{
	if (philo->id % 2 == 0) // philo pair fork droite, puis gauche
	{
		*first_fork = &philo->fork_right;
		*second_fork = &philo->fork_left;
	}
	else
	{
		*first_fork = &philo->fork_left;
		*second_fork = &philo->fork_right;
	}
}

// 123 1 has taken a fork : timestamp (en ld) - id du philo - message
// le philo numero 1 a pris une fourchette 123ms apres le debut du programme.


// start_time = moment où le programme a démarré. // a initialiser 

void eat(t_philo *philo)
{
	pthread_mutex_t *first_fork;
	pthread_mutex_t *second_fork;
	
	if (check_death(philo) == -1)
		return ;
	choose_fork_order(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d has taken a fork\n", get_timestamp(philo->data), philo->id);
	pthread_mutex_lock(second_fork);
	printf("%ld %d has taken a fork\n", get_timestamp(philo->data), philo->id);
	philo->last_time_eaten = get_actual_time_in_ms();
	printf("%ld %d is eating\n", get_timestamp(philo->data), philo->id);
	pthread_mutex_unlock(&philo->data->print);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	
	// a verifier si la fourchette que le philo veut prendre est dispo ou pas avant de la lock
	// satiete++;
	
		
}

