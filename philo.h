/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:37:12 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/11 16:58:29 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>


typedef struct s_info
{

	
}		t_info;


typedef struct s_philo
{
	pthread_mutex_t  fork_r;
	pthread_mutex_t  fork_l;
	
	
}		t_philo;








#endif