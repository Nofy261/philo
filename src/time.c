/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:30:05 by nolecler          #+#    #+#             */
/*   Updated: 2025/05/08 11:47:44 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// start_time = moment où le programme a démarré. // a initialiser 
// get_actual_time() permet de récupérer le temps actuel en millisecondes.
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

// timestamp : moment ou l action a lieu, timestamp = now - start_time
// timestamp : temps ecoulé depuis le début du program
long int get_timestamp(t_data *data)
{
	long int timestamp;

	timestamp = get_actual_time_in_ms() - data->start_time;
	return (timestamp);
}

// met le thread en pause pendant un temps donné tout en permettant au program de vérifier l'état du philo
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_actual_time_in_ms();// debut du moment ou le philo commence a manger
	while ((get_actual_time_in_ms() - start) < milliseconds)
		usleep(500); // 100?
	return (0);
}


