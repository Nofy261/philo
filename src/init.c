/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:43:36 by nolecler          #+#    #+#             */
/*   Updated: 2025/05/02 13:50:03 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int init_philo(t_data *data, t_philo *philo)
{
	int i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].last_time_eaten = data->start_time;
		philo[i].meal_consumed = 0;
		philo[i].id = i + 1;
		philo[i].dead = 0;
		philo[i].finished = 0;
		philo[i].has_thread = 0;
		philo[i].data = data;
		// mutex unique pour chaque philo = fourchette de droite
		if (pthread_mutex_init(&philo[i].fork_right, NULL) != 0) // modif
		//if (pthread_mutex_init(&philo->fork_right, NULL) != 0) // base
		{
			print_error("Error: thread mutex init failed");
			while (--i >= 0) //modif
				pthread_mutex_destroy(&philo[i].fork_right);
			return (-1);
		}
		i++;
	}
	// on relie la fourchette de droite a celle de gauche
	i = 0;
	while (i < data->nb_philo)
	{
		//la fourchette gauche de chaque philo est reliée à la fourchette droite de son voisin à droite.
		data->philo[i].fork_left = data->philo[(i + 1) % data->nb_philo].fork_right;
		i++;
	}
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->start_time = get_actual_time_in_ms();
	data->someone_died = 0;
	if (argv[5])
		data->nb_eat = ft_atoi(argv[5]);
	else
		data->nb_eat = 0;
	if (pthread_mutex_init(&data->death, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (-1); 
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return (-1);
	if (init_philo(data, data->philo) == -1)
	{
		free(data->philo);
		return (-1);
	}
	return (0);
}


int	create_threads(t_data *data, t_philo *philo)
{
	int i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].has_thread = 0; // a voir son utilité ailleurs
		// stock l'id du thread si OK et renvoie 0 et renvoie != 0 si KO
		if (pthread_create(&philo[i].thread, NULL, (void *)routine, &philo[i]) != 0)
		{
			print_error("Error: thread creation failed");
			return (-1);
		}
		philo[i].has_thread = 1;
		i++;
	}
	return (0);
}
