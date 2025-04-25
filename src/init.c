/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:43:36 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/25 14:16:26 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void init_philo(t_data *data, t_philo *philo)
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
	data->someone_died = 0;
	if (argv[5])
		data->nb_eat = ft_atoi(argv[5]);
	else
		data->nb_eat = 0;// modif ft_atoi("0")??
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->print, NULL);
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return ;
	init_philo(data, data->philo);
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
