
#include "philo.h"



// argc ne doit pas etre plus grand que 6 sinon retourne erreur
// les arguments ne doivent etre que des chiffres plus grand que 0 sauf le nombre de repas que chaque philo doit manger sinon message d erreur
// si arg vide : erreur
// si argv[1] > 200 erreur



// int	ft_isdigit(int c)
// {
// 	if (c >= '0' && c <= '9')
// 		return (1);
// 	return (0);
// }


// int parse_args(int argc, char **argv)
// {
//     int i;
//     int j;

//     j = 0;
//     i = 1;
//     while (argv[i])
//     {
//         // cas erreur :
//             // si le premier est un + et que le suivant n est pas un chiffre erreur
//         // si le premier est un chiffre ou espace/tab ou + : on rentre dans la boucle 
//         // 
//         // si c est un chiffre
//         // si c est plus grand que zero
//         // tant que c est espaces/tab on passe
//         // cas a gerer "   24"
//         //             "  2  4" " 87 " " 3"  A GERER DOUBLE QUOTES
//         //             "    +24"
//         //              "  +  24"
//         //              "  +24   "
//         //              " +24+24" non gerer pour le moment 
//         // si cela commence par un moins error
       
//         while (argv[i][j] == 32 || (argv[i][j] >= 9 && argv[i][j] <= 13))
//         {
//             printf("first while valeur argv[i][j]: ", argv[i][j]);
// 		        j++;
//         }
//         while (argv[i][j])
//         {
            
//             if (argv[i][j] == '+' && (ft_isdigit(argv[i][j + 1]) == 0))
//             {
//                 printf("Invalid argument\n");
//                 return (0);
//             }


//             else if (ft_isdigit(argv[i][j]) == 1)
//                 j++;
//             else if (argv[i][j] == '+' && (ft_isdigit(argv[i][j + 1]) == 1))
//                 j++;
//             else
//             {
//                 printf("Invalid argument\n");
//                 return (0);
//             }
//         }
//         i++;
//     }
// }

// if (argc > 6)
// {
//     printf("invalid argument");
//     return (1);
// }