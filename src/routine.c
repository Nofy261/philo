/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:37:21 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/21 17:28:55 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// a mettre dans utils
void print_info(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d %s\n", get_timestamp(philo->data), philo->id, msg);
	pthread_mutex_unlock(&philo->data->print);
}


// a mettre dans fichier checking

int check_death(t_philo *philo)
{
	long int current_time;

	current_time = get_actual_time_in_ms();
	if (current_time - philo->last_time_eaten > philo->data->time_to_die)
	{
		print_info(philo, "died");
		philo->dead = 1;
		return (-1);
	}	
	return (0);
}


void choose_fork_order(t_philo *philo, pthread_mutex_t **first_fork, pthread_mutex_t **second_fork)
{
	if (philo->id % 2 == 0) // philo pair fork droite, puis gauche
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



// 123 1 has taken a fork : timestamp (en ld) - id du philo - message
// le philo numero 1 a pris une fourchette 123ms apres le debut du programme.


// start_time = moment où le programme a démarré. // a initialiser 

void eat(t_philo *philo)
{
	pthread_mutex_t *first_fork;
	pthread_mutex_t *second_fork;
	
	if (check_death(philo) == -1)
		return ;
	// avant de choisir il faut check disponibilté
	choose_fork_order(philo, &first_fork, &second_fork);
	
	pthread_mutex_lock(first_fork);
	print_info(philo, "has taken a fork");
	
	pthread_mutex_lock(second_fork);
	print_info(philo, "has taken a fork");
	
	philo->last_time_eaten = get_actual_time_in_ms();
	print_info(philo, "is eating");
	
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	
	// a verifier si la fourchette que le philo veut prendre est dispo ou pas avant de la lock
	// satiete++;
	// ici incrementer argv[5](si present)
		
}
