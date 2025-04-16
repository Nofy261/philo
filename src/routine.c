/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:37:21 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/16 16:38:21 by nolecler         ###   ########.fr       */
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

void eat(t_philo *philo)
{
	if (check_death(philo) == -1)
		return ;
	// verifier si les deux fourchettes sont dispo
	
	if (philo->id % 2 == 0) // philo pair fork droite, puis gauche
	{
		pthread_mutex_lock(&philo->fork_right);
		pthread_mutex_lock(&philo->fork_left);
	}
	else // philo impair gauche puis droite
	{
		pthread_mutex_lock(&philo->fork_left);
		pthread_mutex_lock(&philo->fork_right);
	}
	pthread_mutex_lock(&philo->data->print);
	printf("philo is eating"); // le id du philo ??
	pthread_mutex_unlock(&philo->data->print);
	philo->last_meal = 1;
	
	
		
}
// le temps ecoulee sera utiliser pour etre comparer au time_to_die


// verifier si le philo n'est pas mort
// eat = prendre les fourchettes : verifier si ce n'est pas dispo il attend
// si la fourchette est dispo , il le prend et verouille le mutex (faire pareil pour les 2fourchettes)
// print take a fork (entre mutex locked et unlocked)
// un temps precis de delai de repas
// deverouille le mutex (fourchette) quand il a fini de manger 
// 
