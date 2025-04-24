/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:33:35 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/24 16:54:37 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	int		i;
    t_data data;
	
    init_data(&data, argv);
    if (parse_args(argv) == 1)
        return (1);
	if (create_threads(&data, data.philo) == -1)
		return (1);	
    if (simulation(&data) == -1)
		return (1);
	


	//pthread_mutex_destroy
	pthread_mutex_destroy(&data.print);
	pthread_mutex_destroy(&data.death);

	 // Détruire les mutex de chaque philo
	i = 0;
	while (i < data.nb_philo)
	{
		pthread_mutex_destroy(&data.philo[i].fork_right);
		pthread_mutex_destroy(&data.philo[i].fork_left);
		i++;
	}
    return (0);
    
}

