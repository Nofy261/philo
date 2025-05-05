/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:43:21 by nolecler          #+#    #+#             */
/*   Updated: 2025/05/05 13:22:38 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void print_info(t_philo *philo, char *msg)
{
	long	time;

	time = get_timestamp(philo->data);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print);
}

void print_info2(t_philo *philo, char *msg) // modif
{
	long	time;

	time = get_timestamp(philo->data);
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->someone_died == 1)
		printf("%ld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->death);
	pthread_mutex_unlock(&philo->data->print);
}