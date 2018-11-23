/*--------------------------------------------------------------*/
/* Reussites. Cecile Dumas, Catherine Parent, octobre 2005,
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>
#include "MD.h"

/* Interaction avec l'utilisateur */

/* ----------------------------------------------------------
 * CONSTANTES MODE ET JEU
 * ----------------------------------------------------------
*/


#define         TexteNbASimuler          "Choisissez le nombre de parties a simuler : "
#define         TexteNbAAnalyser         "Choisissez le nombre de parties a analyser : "

#define         nbMaxEssais              5
#define         Invite                   "Choisissez votre mode de jeu  (? pour obtenir de de l'aide) : "
#define         TexteSimulation          '1'
#define         TexteAnalyse             '2'
#define         TexteRetour              'R'
#define         TexteAideMode            '?'
#define         TexteFin                 'F'



/* -------------------------------------------------------------------
 * CodeCommande   : le type [SIMULMD, ANALYSEMD, FIN]
 * -------------------------------------------------------------------
*/

typedef enum {R7, MD, AIDE, FINJ}        CodeJeu ;
typedef enum {SIMUL, ANALYSE, RETOUR}      CodeCommande ;



/* -------------------------------------------------------------------
 *      INTERACTION
 *
 *      EstTexteCommande : un caract�re ---> un bool�en
 *      EcrireMenu       : une action
 *      SaisirCommande   : une action (le r�sultat : un CodeCommande)
 * -------------------------------------------------------------------
*/




/*CHOIX DU JEU*/


void	LireCar (char	*c)
{
    int l ;
    while (isspace ( l=getchar ())) ;
    *c = l ;
}


void EcrireMenuChoixJeu ()
{
    printf ("Tapez \n") ;
    printf (" 1 pour jouer aux relais des 7(R7), \n") ;
    printf (" 2 pour jouer à Montée-Descente, \n");
    printf (" F pour Fin, \n");
    printf (" ? pour Aide.\n");
}


int EstTexteCommandeJeu (char c)
{
    return
        ((c == TexteSimulation) ||
         (c == TexteAnalyse) ||
         (c == TexteFin)) ;
}



void SaisirJeu (CodeJeu *CJ)
{
    char codeJ  ;
    int  nbEssais;

    printf ("Quel est votre choix de jeu ?\n") ;
    EcrireMenuChoixJeu ();
    LireCar (&codeJ) ;
    nbEssais = 0 ;

    while ((nbEssais < nbMaxEssais) && (! EstTexteCommandeJeu(codeJ)))
    {
        if (codeJ == '?')
        {
            EcrireMenuChoixJeu() ;
            LireCar (&codeJ) ;
        }
        else
        {
            printf ("Commande incorrecte.\n");
            nbEssais++ ;
            if (nbEssais < nbMaxEssais)
            {
                printf ("Quel est votre choix de jeu ?\t") ;
                LireCar (&codeJ) ;
            }
        }
    }
    if (nbEssais == nbMaxEssais)
        *CJ = FINJ  ;
    else
        switch (codeJ)
        {
        case '1':
            *CJ = R7;
            break ;
        case '2' :
            *CJ = MD ;
            break ;
        case 'F' :
            *CJ = FINJ ;
            break ;
        case '?' :
            *CJ = AIDE ;
            break ;
        }
}




/*CHOIX DU MODE*/



int EstTexteCommandeMode (char c)
{
    return
        ((c == TexteSimulation) ||
         (c == TexteAnalyse) ||
         (c == TexteRetour));
}

void EcrireMenuChoixMode ()
{
    printf ("Tapez \n") ;
    printf (" %c pour Simulation graphique de la reussite, \n",TexteSimulation) ;
    printf (" %c pour Analyse d une serie de reussites (sans affichage graphique), \n",TexteAnalyse);
    printf (" %c pour Retour au choix du jeu,\n",TexteRetour);
    printf (" %c pour Fin, \n",TexteFin);
    printf (" %c pour Aide.\n",TexteAideMode);
}


void SaisirCommande (CodeCommande *CC)
{
    char C  ;
    int  nbEssais ;

    printf (Invite) ;

    LireCar (&C) ;
    nbEssais = 0 ;
    while ((nbEssais < nbMaxEssais) && (! EstTexteCommandeMode(C)))
    {
        if (C == TexteAideMode)
        {
            EcrireMenuChoixMode();
            LireCar (&C) ;
        }
        else
        {
            printf ("Commande incorrecte.");
            nbEssais++ ;
            if (nbEssais < nbMaxEssais)
            {
                printf (Invite) ;
                LireCar (&C) ;
            }
        }
    }
    if (nbEssais == nbMaxEssais)
        *CC = RETOUR  ;
    else
        switch (C)
        {
        case TexteSimulation :
            *CC = SIMUL ;
            break ;
        case TexteAnalyse :
            *CC = ANALYSE ;
            break ;
        case TexteRetour :
            *CC = RETOUR ;
            break ;
        }
}



/*RUN EN FONCTION DU JEU + MODE*/

void runSimulerR7(int NBMAXT)
{

    int nbparties;
    printf(TexteNbASimuler);
    scanf("%d",&nbparties);
    OuvrirGraphique("Relai 7");
    ObserverR7(nbparties, NBMAXT);
    FermerGraphique();
}

void runAnalyserR7(int NBMAXT)
{
    int nbparties;
    printf(TexteNbAAnalyser);
    scanf("%d",&nbparties);
    printf("analyser - R7 \n");

    /* todo MARCO */

    /*AnalyserR7(nbparties,NBMAXT);*/
}

void runSimulerMD(int NBSTOCK)
{
    int nbparties;
    printf(TexteNbASimuler);
    scanf("%d",&nbparties);
    OuvrirGraphique("Montée-Descente");
    ObserverMD(nbparties, NBSTOCK);
    FermerGraphique();
}

void runAnalyserMD(int NBSTOCK)
{
    int nbparties;
    printf(TexteNbAAnalyser);
    scanf("%d",&nbparties);
    printf("analyser - MD\n ");
    /* todo ANTOINE */
    AnalyserMD(nbparties, NBSTOCK);
}
