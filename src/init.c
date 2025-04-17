
#include "philo.h"

void init_data(t_data *data, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->start_time = get_actual_time_in_ms();
	if (argv[5])
		data->nb_eat = ft_atoi(argv[5]);
	else
		data->nb_eat = -1;
	pthread_mutex_init(&data->print, NULL);
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return ;
}

void init_philo(t_data *data, t_philo *philo)
{
	int i;
	int j;

	i = 0;
	while (i < data->nb_philo)
	{
		philo->last_time_eaten = 0;
		philo->id = i + 1;
		philo->dead = 0;
		philo->finished = 0;
		philo->data = data;
		// mutex unique pour chaque philo = fourchette de droite
		j = pthread_mutex_init(&philo->fork_right, NULL); // i commence a 0 
		{
			if (j != 0)
			return ;
		}
		i++;
	}
	// on relie la fourchette de droite a celle de gauche
	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].fork_left = data->philo[(i + 1) % data->nb_philo].fork_right;
		i++;
	}
}

// a appeler dans le main apres initialisation
int	create_threads(t_data *data, t_philo *philo)
{
	int i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
			return (-1);
		i++;
	}
	// routine = manger , dormir , penser(check if_is_dead entre)
	return (0);
}
