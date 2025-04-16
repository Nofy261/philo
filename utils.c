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
