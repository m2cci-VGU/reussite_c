/*--------------------------------------------------------------*/
/* Reussites. Cecile Dumas, Catherine Parent, octobre 2005,
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/


/* Interaction avec l'utilisateur */


typedef enum {R7, MD, AIDE, FINJ}        CodeJeu ;
typedef enum {SIMUL, ANALYSE, RETOUR}      CodeCommande ;


void SaisirJeu (CodeJeu *CJ);

void SaisirCommande (CodeCommande *);

void EcrireMenuChoixJeu ();


void runSimulerR7(int NBMAXT);

void runAnalyserR7(int NBMAXT);

void runSimulerMD();

void runAnalyserMD();
