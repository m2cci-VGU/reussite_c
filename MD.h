#include "AfficherTas.h"
#define NOMBRE_DE_STOCK 4
#define temps 800000

void ObserverMD(int);
void AnalyserMD(int);

Tas* getTalonMD();
Tas* getTasCouleurMD(Couleur);
Tas* getTasDefausseMD(int);
void CreerTableauInitialMD();
void JouerUneMD(ModeTrace, booleen*);
