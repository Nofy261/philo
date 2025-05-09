/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:33:35 by nolecler          #+#    #+#             */
/*   Updated: 2025/05/09 10:02:08 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


int main(int argc, char **argv)
{
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
		cleanup(&data);
        free(data.philo);
        return (1);
    }
	cleanup(&data);   
    free(data.philo);
    return (0);
}



