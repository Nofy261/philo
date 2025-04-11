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


typedef struct s_data
{
	int					nb_eat;
	int					nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long			start;//
	pthread_mutex_t		print;
	struct			s_philo *philo;
}		t_data;


typedef struct s_philo
{
	struct			s_data  *data;
	int			last_meal;
	int				id;
	int				dead;
	int				finished;
	pthread_t		thread;
	pthread_mutex_t  fork_right;
	pthread_mutex_t  fork_left;
	
}		t_philo;



int	ft_atoi(char *str);
void init_data(t_data *data, char **argv);
void init_philo(t_data *data);





#endif