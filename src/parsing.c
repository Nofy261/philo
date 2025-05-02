/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:47:32 by nolecler          #+#    #+#             */
/*   Updated: 2025/05/02 13:52:02 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	is_zero(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] != '0')
			return (0);
		i++;
	}
	return (-1);
}

static int	is_empty_or_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
			return (0);
		i++;
	}
	return (-1);
}

static int	is_invalid_format(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (str[i] == '\0' || ft_isdigit(str[i]) == 0)
	{
		print_error("Invalid argument: expected digits");
		return (-1);
	}
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
		{
			print_error("Invalid argument: non-digit found");
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	is_invalid_argument(char *arg)
{
	int	i;

	i = 0;
	if (is_empty_or_whitespace(arg) == -1)
	{
		print_error("empty or whitespace only is invalid");
		return (-1);
	}
	while (arg[i] == ' ' || (arg[i] >= 9 && arg[i] <= 13))
		i++;
	if (is_zero(arg + i) == -1)
	{
		print_error("only zero is invalid");
		return (-1);
	}
	if (is_invalid_format(arg + i) == -1)
		return (-1);
	return (0);
}

int	parse_args(char **argv)
{
	int	i;
	int	argc;

	i = 1;
	argc = 0;
	if (check_number_of_philo(argv[1]) == -1)
		return (-1);
	while (argv[i])
	{
		if (is_invalid_argument(argv[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
