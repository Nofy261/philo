/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:41:51 by nolecler          #+#    #+#             */
/*   Updated: 2025/05/02 13:51:11 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


int	check_number_of_philo(char *str)
{
	if (ft_atoi(str) < 1 || ft_atoi(str) > 200)
	{
		ft_putstr_fd("Number of philo is invalid\n", 2);
		return (-1);
	}
	return (0);
}
