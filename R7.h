/*--------------------------------------------------------------*/
/* Reussites. Michel Bonin, Catherine Parent, octobre 2005,
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

/* Le relais des 7 */

#include "AfficherTas.h"

void ObserverR7(int, int);
void AnalyserR7(int, int);

Tas* getTalonR7 ();
Tas* getRebutR7 ();
Tas* getTasCouleurR7(Couleur Co);
void CreerTableauInitialR7();
int JouerUneR7(int, ModeTrace);
