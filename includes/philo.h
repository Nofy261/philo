/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:37:12 by nolecler          #+#    #+#             */
/*   Updated: 2025/05/08 12:01:12 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct s_data;

typedef struct s_philo
{
	long int 		last_time_eaten;
	int				meal_consumed;
	int				id;
	int 			has_thread;
	pthread_t 		thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t		time_mutex;
	pthread_mutex_t		meal_mutex;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int 			nb_eat;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				someone_died;
	long int		start_time;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_mutex_t	*forks; 
	t_philo 		*philo;
}					t_data;

// CHECKING.C
int					check_death(t_philo *philo);
int					simulation(t_data *data);

// EAT.C
int				philo_eat(t_philo *philo);

// INIT.C
int					init_data(t_data *data, char **argv);
void 				init_philo(t_data *data, t_philo *philo);
int					create_threads(t_data *data, t_philo *philo);

// PARSING_UTILS
// int		check_number_of_args(int argc);
int					check_number_of_philo(char *str);

// PARSING.C
int					parse_args(char **argv);

// PHILO_UTILS.C
void				print_info(t_philo *philo, char *msg);
void				cleanup(t_data *data);


// ROUTINE.C
void				*routine(void *arg);

// TIME.C
long int			get_actual_time_in_ms(void);
long int			get_timestamp(t_data *data);
//int 				ft_usleep(size_t milliseconds);// A VOIR

// UTILS.C
int					ft_atoi(char *str);
int					ft_isdigit(int c);
size_t				ft_strlen(const char *s);
void				print_error(char *msg);
void				ft_putstr_fd(char *str, int fd);

#endif