/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:30:05 by nolecler          #+#    #+#             */
/*   Updated: 2025/05/09 13:38:43 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	get_actual_time_in_ms(void)
{
	struct timeval	time;
	long int		ms;

	if (gettimeofday(&time, NULL) == -1)
	{
		ft_putstr_fd("gettimeofday failed\n", 2);
		return (-1);
	}
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

long int	get_timestamp(t_data *data)
{
	long int	timestamp;

	timestamp = get_actual_time_in_ms() - data->start_time;
	return (timestamp);
}
