#include "AfficherTas.h"
#define NOMBRE_DE_STOCK_MAX 8
#define temps 300000


void ObserverMD(int, int);
void AnalyserMD(int, int);

Tas* getTalonMD();
Tas* getTasCouleurMD(Couleur);
Tas* getTasDefausseMD(int);
void CreerTableauInitialMD();
void JouerUneMD(ModeTrace, booleen*);
