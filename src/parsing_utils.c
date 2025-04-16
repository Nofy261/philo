/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:41:51 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/16 10:47:24 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_number_of_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("Number of arguments is invalid\n", 2);
		return (-1);
	}
	return (0);
}

int	check_number_of_philo(char *str)
{
	if (ft_atoi(str) < 1)
	{
		ft_putstr_fd("Number of philo is invalid\n", 2);
		return (-1);
	}
	return (0);
}
