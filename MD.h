#include "AfficherTas.h"
#define NOMBRE_DE_STOCK 6

void ObserverMD(int);
void AnalyserMD(int);

Tas* getTalonMD();
Tas* getTasCouleurMD(Couleur);
Tas* getTasDefausseMD(int);
void CreerTableauInitialMD();
void JouerUneMD(ModeTrace, int*);
