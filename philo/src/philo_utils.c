/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:43:21 by nolecler          #+#    #+#             */
/*   Updated: 2025/05/12 17:24:48 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_info(t_philo *philo, char *msg)
{
	long	time;

	time = get_timestamp(philo->data);
	if (check_death(philo) == 0)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%ld %d %s\n", time, philo->id, msg);
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
}

void	print_death(t_philo *philo, char *msg)
{
	long	time;

	time = get_timestamp(philo->data);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (data->philo[i].has_thread == 1)
			pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i].fork_mutex);
		pthread_mutex_destroy(&data->philo[i].meal_mutex);
		pthread_mutex_destroy(&data->philo[i].time_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->death);
	free(data->forks);
}

int	check_number_of_philo(char *str)
{
	if (ft_atoi(str) < 1 || ft_atoi(str) > 200)
	{
		ft_putstr_fd("Number of philo is invalid\n", 2);
		return (-1);
	}
	return (0);
}

void	print_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}
