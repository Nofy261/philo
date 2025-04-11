
#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	counter;
	int	stock;

	i = 0;
	counter = 1;
	stock = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			counter = counter * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		stock = stock * 10 + (str[i] - '0');
		i++;
	}
	return (stock * counter);
}



void init_data(t_data *data, char **argv)
{
    data->nb_philo = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);

    if (argv[5])
        data->nb_eat = ft_atoi(argv[5]);
    else
        data->nb_eat = -1;

    data->start = 0;
    pthread_mutex_init(&data->print, NULL);

    data->philo = malloc(sizeof(t_philo) * data->nb_philo);
    if (!data->philo)
        return ;
}

void init_philo(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nb_philo)
    {
        t_philo *philo = &data->philo[i];
        philo->data = data;
        philo->id = i + 1;
        philo->last_meal = 0;
        philo->dead = 0;
        philo->finished = 0;
        pthread_mutex_init(&philo->fork_right, NULL);
        // Le fork_left pointera vers le fork_right du voisin
        i++;
    }

    // Setup des fork_left une fois tous les mutex init
    i = 0;
    while (i < data->nb_philo)
    {
        data->philo[i].fork_left = data->philo[(i + 1) % data->nb_philo].fork_right;
        i++;
    }
}