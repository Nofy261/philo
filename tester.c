#include "philo.h"

#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>

// Déclaration de ta fonction à tester
int parse_args(char **argv);

// Couleurs ANSI flashy
#define LIGHT_GREEN   "\033[1;92m"
#define LIGHT_RED     "\033[1;91m"
#define RESET         "\033[0m"

// Structure de test
typedef struct {
    char *name;
    char **args;
    int expected; // 0 = valide, 1 = invalide
} TestCase;

int main(void)
{
    TestCase tests[] = {
        {"Valid: +123", (char *[]){"./a.out", "+123", NULL}, 0},
        {"Valid: 42", (char *[]){"./a.out", "42", NULL}, 0},
        {"Valid: spaces + number", (char *[]){"./a.out", "     +56", NULL}, 0},
        {"Invalid: only zero", (char *[]){"./a.out", "      000", NULL}, 1},
        {"Invalid: empty", (char *[]){"./a.out", "     ", NULL}, 1},
        {"Invalid: letters", (char *[]){"./a.out", "abc", NULL}, 1},
        {"Invalid: + then letters", (char *[]){"./a.out", "+abc", NULL}, 1},
        {"Valid: multiple numbers", (char *[]){"./a.out", "123", "456", "+789", NULL}, 0},
        {"Invalid: mixed valid and zero", (char *[]){"./a.out", "123", "000", NULL}, 1},
        {NULL, NULL, 0} // Fin
    };

    int passed = 0;
    int total = 0;

    for (int i = 0; tests[i].name != NULL; i++)
    {
        int result = parse_args(tests[i].args);
        total++;
        if (result == tests[i].expected)
        {
            printf("%s: " LIGHT_GREEN "OK" RESET "\n", tests[i].name);
            passed++;
        }
        else
        {
            printf("%s: " LIGHT_RED "ERROR" RESET "\n", tests[i].name);
        }
    }

    // Résumé final
    printf("\nRésultat : %s%d OK%s / %d tests\n",
        LIGHT_GREEN, passed, RESET, total);

    if (passed != total)
        printf(LIGHT_RED "❌ Certains tests ont échoué.\n" RESET);
    else
        printf(LIGHT_GREEN "✅ Tous les tests ont réussi !\n" RESET);

    return 0;
}
