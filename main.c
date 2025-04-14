/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:33:35 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/14 16:52:42 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

// cas erreur :

// ./philo av[1]=nbre de philo av[2]=time_die av[3]=time_eat av[4]=time_sleep av[5]=nbre_of_time_each_must_eat(facultatif) 

// le nombre d arguments  ✅
// nombre maximum a ne pas depasser Ex: 33333  26434683463498463 48374387 748338 ???  A FAIRE 
// // si ce n est pas un digit erreur : a gerer cet exemple *5784
// le double quote pose probleme 
//  ./a.out "46 347 0" --> Invalid argument: non-digit found% 

// if argv[1] < 1 = error doit y avoir au moins un philo

int	check_number_of_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("Number of arguments is invalid\n", 2);
		return (-1);
	}
	return (0);
}

int check_number_of_philo(char *str)
{
    if (ft_atoi(str) < 1)
    {
        ft_putstr_fd("Number of philo is invalid\n", 2);
        return (-1);
    }
    return (0);
}

int is_zero(char *str)
{
    int i = 0;

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
    return (1);
}

int is_empty_or_whitespace(char *str)
{
    int i;
	
	i = 0;
    while (str[i])
    {
        if (!(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
            return (0);
        i++;
    }
    return (-1);
}

int print_error(char *msg)
{
    ft_putstr_fd(msg, 2);
    ft_putstr_fd("\n", 2);
    return (1);
}


int has_invalid_format(char *str)
{
    int i;
    
    i = 0;
    if (str[i] == '+')
        i++;
    if (str[i] == '\0' || !ft_isdigit(str[i]))
        return (print_error("Invalid argument: expected digits"));
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (print_error("Invalid argument: non-digit found"));
        i++;
    }
    return (0);
}

int is_invalid_argument(char *arg)
{
    int j;
    
    j = 0;
    if (is_empty_or_whitespace(arg) == -1)
        return (print_error("empty or whitespace only is invalid"));
    while (arg[j] == ' ' || (arg[j] >= 9 && arg[j] <= 13))
        j++;
    if (is_zero(arg + j) == 1)
        return (print_error("only zero is invalid"));
    if (has_invalid_format(arg + j))
        return (1);
    return (0);
}

int parse_args(char **argv)
{
    int i;
    
    i = 1;
    while (argv[i])
    {
        if (is_invalid_argument(argv[i]))
            return (1);
        i++;
    }
    return (0);
}






// int parse_args(char **argv)
// {
//     int i;
//     int j;
	
// 	i = 1;
//     while (argv[i])
//     {
//         if (is_empty_or_whitespace(argv[i]) == -1)
//         {
//             printf("je suis espace ou vide\n");
//             ft_putstr_fd("empty or whitespace only is invalid", 2);
//             return (1);
//         }
//         j = 0;
//         while (argv[i][j] == ' ' || (argv[i][j] >= 9 && argv[i][j] <= 13))
//             j++;
//         if (is_zero(argv[i] + j))
//         {
//             printf("je suis 0 seul\n");
//             ft_putstr_fd("only zero is invalid", 2);
//             return (1);
//         }
//         if (argv[i][j] == '+')
//             j++;
//         if (ft_isdigit(argv[i][j]) == 0)
//         {
//             printf("je suis ici AA\n"); // -43; abc; ++67; 
//             ft_putstr_fd("Invalid argument: expected digits", 2);
//             return (1);
//         }
//         while (argv[i][j])
//         {
//             if (ft_isdigit(argv[i][j]) == 0)
//             {
//                 printf("je suis ici BB\n"); // +45+67 , "  765  "
//                 ft_putstr_fd("Invalid argument: non-digit found", 2);
//                 return (1);
//             }
//             j++;
//         }
//         i++;
//     }
//     return (0);
// }


// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	int i;

// 	i =  parse_args(argv);
// }