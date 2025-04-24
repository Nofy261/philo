/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:43:36 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/24 16:33:49 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void init_philo(t_data *data, t_philo *philo)
{
	int i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo->last_time_eaten = 0;
		philo->meal_consumed = 0;
		philo->id = i + 1;
		philo->dead = 0;
		philo->finished = 0;
		philo->data = data;
		// mutex unique pour chaque philo = fourchette de droite
		if (pthread_mutex_init(&philo->fork_right, NULL) != 0)
		{
			print_error("Error: thread mutex init failed");
			exit(1);
			// return ; a voir ??
		}
		i++;
	}
	// on relie la fourchette de droite a celle de gauche
	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].fork_left = data->philo[(i + 1) % data->nb_philo].fork_right;
		i++;
	}
}
void init_data(t_data *data, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->start_time = get_actual_time_in_ms();
	if (argv[5])
		data->nb_eat = ft_atoi(argv[5]);
	else
		data->nb_eat = 0;
	pthread_mutex_init(&data->print, NULL);
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return ;
	init_philo(data, data->philo);
}


// a appeler dans le main apres initialisation
int	create_threads(t_data *data, t_philo *philo)
{
	int i;

	i = 0;
	while (i < data->nb_philo)
	{
		// stock l'id du thread si OK et renvoie 0 et renvoie != 0 si KO
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
		{
			print_error("Error: thread creation failed");
			return (-1);
		}
		i++;
	}
	i = 0;
	while(i < data->nb_philo)
	{
		// permet de signaler au programme ppal tel philo a terminer sa routine
		// ensuite le programme peut se liberer proprement
        if (pthread_join(philo[i].thread, NULL) != 0)
		{
			print_error("Error: thread join failed");
			return (-1);
		}
		i++;
    }
	return (0);
}

// routine = manger , dormir , penser(check if_is_dead entre)
