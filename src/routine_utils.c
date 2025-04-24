/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:43:21 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/23 12:51:24 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_info(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d %s\n", get_timestamp(philo->data), philo->id, msg);
	pthread_mutex_unlock(&philo->data->print);
}

