/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:37:12 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/16 13:40:09 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>


typedef struct s_data
{
	int					nb_eat; // nb_of_times_philo_must_eat;
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	pthread_mutex_t		print;
	t_philo 			*philo;
}		t_data;


typedef struct s_philo
{
	int					last_meal;
	int					id;
	int					dead;
	int					finished;
	pthread_t			thread;// action de chaque philo
	pthread_mutex_t  	fork_right;
	pthread_mutex_t  	fork_left;
	t_data				*data;	
}		t_philo;


// UTILS
int		ft_atoi(char *str);
int		ft_isdigit(int c);
void	ft_putstr_fd(char *str, int fd);
size_t	ft_strlen(const char *s);

// INITS.C
void 	init_data(t_data *data, char **argv);
void 	init_philo(t_data *data, t_philo *philo);

// PARSING_UTILS
int		check_number_of_args(int argc);
int 	check_number_of_philo(char *str);

// PARSING.C
int 	parse_args(char **argv);







#endif