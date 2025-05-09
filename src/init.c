/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:43:36 by nolecler          #+#    #+#             */
/*   Updated: 2025/05/09 13:37:49 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].last_time_eaten = data->start_time;
		philo[i].meal_consumed = 0;
		philo[i].id = i + 1;
		philo[i].has_thread = 0;
		philo[i].data = data;
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		pthread_mutex_init(&philo[i].time_mutex, NULL);
		pthread_mutex_init(&philo[i].meal_mutex, NULL);
		i++;
	}
}

static int	allocate_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(t_fork) * data->nb_philo);
	if (!data->forks)
	{
		pthread_mutex_destroy(&data->death);
		pthread_mutex_destroy(&data->print);
		return (-1);
	}
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i].fork_mutex, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

static int	allocate_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
	{
		pthread_mutex_destroy(&data->death);
		pthread_mutex_destroy(&data->print);
		free(data->forks);
		return (-1);
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
	data->stop_sim = 0;
	if (argv[5])
		data->nb_eat = ft_atoi(argv[5]);
	else
		data->nb_eat = 0;
	if (pthread_mutex_init(&data->death, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (-1);
	if (allocate_forks(data) == -1)
		return (-1);
	if (allocate_philo(data) == -1)
		return (-1);
	init_philo(data, data->philo);
	return (0);
}

int	create_threads(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].has_thread = 0;
		if (pthread_create(&philo[i].thread, NULL, (void *)routine,
				&philo[i]) != 0)
		{
			print_error("Error: thread creation failed");
			return (-1);
		}
		philo[i].has_thread = 1;
		i++;
	}
	return (0);
}
