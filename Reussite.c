/*--------------------------------------------------------------*/
/* Reussites. Cecile Dumas, Catherine Parent, octobre 2005,
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

#include <stdio.h>

/* Programme principal */
#include "MD.h"
#include "R7.h"
#include "InteractionReussite.h"
#include "Alea.h"


/* -------------------------------------------------------------------
 *      PROGRAMME PRINCIPAL AVEC MENU D'INTERACTION
 * -------------------------------------------------------------------
 */
#define         TexteBienvenue           "Bienvenue ! \n"
#define         TexteAuRevoir            "Dommage, au revoir ! \n"


int main(void)
{
    int NBMAXT;
	  int NBSTOCK;

    CodeCommande    Commande ;
    int nbparties ;
    CodeJeu CJ;


    InitAlea();

    printf (TexteBienvenue) ;

    SaisirJeu(&CJ);

    while(CJ != FINJ)
    {
      if (CJ == R7)
      {
          printf("Choix du nombre de tours maximum: \n");
          scanf("%d", &NBMAXT);
      }
      else
      {
          NBMAXT = 3;
      }

      if (CJ == MD)
      {
      printf("Combien de stock voulez-vous (minimum 1, maximum 8)?");
      scanf("%d", &NBSTOCK);
          if (NBSTOCK>8){
          NBSTOCK=8;
          }
          else if (NBSTOCK<0){
          NBSTOCK=1;
          }
      }

        switch (CJ)
        {
        case AIDE :
            EcrireMenuChoixJeu ();
            break;
        case R7 :
            SaisirCommande (&Commande) ;
            while (Commande != RETOUR)
            {
                switch  (Commande)
                {
                case SIMUL :
                    runSimulerR7(NBMAXT);
                    break ;
                case ANALYSE:
                    runAnalyserR7(NBMAXT);
                    break;
                }
                SaisirCommande (&Commande) ;
            }
            printf (TexteAuRevoir) ;
            break;

        case MD :
            SaisirCommande (&Commande) ;
            while (Commande != RETOUR)
            {
                switch  (Commande)
                {
                case SIMUL :
                    runSimulerMD(NBSTOCK);
                    break ;
                case ANALYSE :
                    runAnalyserMD(NBSTOCK);
                    break;
                }
                SaisirCommande (&Commande) ;
            }
            printf (TexteAuRevoir) ;
            break;
        }
        SaisirJeu(&CJ);
    }

    return 0;
}
