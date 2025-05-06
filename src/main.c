/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:33:35 by nolecler          #+#    #+#             */
/*   Updated: 2025/05/06 10:31:52 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


int main(int argc, char **argv)
{
    int		i;
    t_data	data;
    
    if (argc < 5 || argc > 6)
    {
        ft_putstr_fd("Number of arguments is invalid\n", 2);
        return (1);
    }
    if (parse_args(argv) == -1 || init_data(&data, argv) == -1)
        return (1);
    if (create_threads(&data, data.philo) == -1)
    {
        if (data.philo)
            free(data.philo);
        return (1);
    }
    if (simulation(&data) == -1)
    {
        free(data.philo);
        return (1);
    }
    i = 0;
	while (i < data.nb_philo)// a voir
    {
		if (data.philo[i].has_thread)
        	pthread_join(data.philo[i].thread, NULL);
        i++;
    }
	// join = pour detruire les threads;
	// destroy = mutex
	// free  
    pthread_mutex_destroy(&data.print);
    pthread_mutex_destroy(&data.death);
	i = 0;
    while (i < data.nb_philo)
    {
        pthread_mutex_destroy(data.philo[i].fork_right);
        pthread_mutex_destroy(data.philo[i].fork_left);
		//pthread_mutex_destroy(&data.forks[i]); // ??
        i++;
    }
    free(data.philo);
    return (0);   
}

