/*--------------------------------------------------------------*/
/* Reussites. Michel Bonin, Catherine Parent, octobre 2005,
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

/* Gï¿½nï¿½rateur alï¿½atoire */

//Coucou de vincent

#include <stdlib.h>
#include <time.h>
///salut de la part de Marco//

void InitAlea()
{
  int g;
  time_t t;

  g = (unsigned int) time(&t);
  srand(g);
}

int UnEntier(int n)
{
  /* tirage aléatoire d'un entier entre 1 et n */
  return rand()%n + 1;
}
