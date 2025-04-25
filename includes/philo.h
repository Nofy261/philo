/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:37:12 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/25 10:41:22 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h> // ??
# include <sys/time.h>


struct s_data; 

typedef struct s_philo
{
    long int            last_time_eaten;// heure du dernier repas
    int                    meal_consumed;// non initialisé;
    int                    id;
    int                    dead;
    int                    finished;
    pthread_t            thread;// action de chaque philo
    pthread_mutex_t      fork_right;
    pthread_mutex_t      fork_left;
    struct s_data        *data;
}        t_philo;

typedef struct s_data
{
    int                    nb_eat; // nb_of_times_philo_must_eat;
    int                    nb_philo;
    int                    time_to_die;
    int                    time_to_eat;
    int                    time_to_sleep;
    int                    someone_died;
    long int            start_time;
    pthread_mutex_t        print;
    pthread_mutex_t        death;
    t_philo             *philo; // a ne pas mettre ??? 
}        t_data;



// CHECKING.C
int		check_death(t_philo *philo);
int		simulation(t_data *data);


// EAT.C
void	eat(t_philo *philo);


// INIT.C
void 	init_data(t_data *data, char **argv);
void 	init_philo(t_data *data, t_philo *philo);
int		create_threads(t_data *data, t_philo *philo);


// PARSING_UTILS
//int		check_number_of_args(int argc);
int 	check_number_of_philo(char *str);


// PARSING.C
int 	parse_args(char **argv);


// ROUTINE_UTILS.C
void print_info(t_philo *philo, char *msg);


// ROUTINE.C
//void	routine(t_philo *philo);
void *routine(void *arg);

// TIME.C
long int	get_actual_time_in_ms(void);
long int	get_timestamp(t_data *data);
int			ft_usleep(size_t milliseconds);


// UTILS.C
int		ft_atoi(char *str);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
void	print_error(char *msg);
void	ft_putstr_fd(char *str, int fd);













#endif