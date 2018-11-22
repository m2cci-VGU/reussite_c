#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TasACompleter.h"

int main()
{
    /*TAS*/
        Tas T1;
        Tas T2;
        Tas T3;
        int N1 = 52;
        Localisation L1;
        L1.NL = 1 ;
        L1.NC = 1 ;
        char message1;
        int N2 = 32;
        Localisation L2;
        L2.NL = 1 ;
        L2.NC = 1 ;
        char message2;
        int N3 = 32;
        Localisation L3;
        L3.NL = 1 ;
        L3.NC = 1 ;
        char message3;

    /*cartes*/
    Carte C;
    C.RC = Quatre;
    C.CC = Carreau;
    C.VC = Decouverte;

    Carte C1;
    C1.RC = Dame;
    C1.CC = Coeur;
    C1.VC = Decouverte;

    Carte C2;
    C2.RC = Valet;
    C2.CC = Pique;
    C2.VC = Cachee;

  afficherCarte(C1);
    afficherCarte(C2);

    testCarte(C1);
    testCarteBooleen(C1, C2);

CreerJeuNeuf(N1, L1, &T1);
afficherTasPourTest(T1);
testBoolenTas(T1);
testLocalisationPlaceTas(T1);

//RetournerTas(&T1);
//afficherTasPourTest(T1);


};



void afficherTasPourTest(Tas T)
{
    struct adCarte *visiteur = T.tete;

    printf("Le TAS est [ ") ;
    while (visiteur != NULL)
    {
        printf("%d%d%d ", visiteur->elt.RC, visiteur->elt.CC, visiteur->elt.VC) ;
        visiteur = visiteur->suiv;
    }
    printf("]\n");
}

void afficherCarte(Carte C)
{
    printf("La carte est le %d de %d, elle est %d\n", C.RC, C.CC, C.VC);
}


void testCarte(Carte C1)
{
    printf("Rang suivant : %d\n", RangSuivant(C1.RC));
    printf("Rang : %d\n", LeRang(C1));
    printf("Couleur : %d\n", LaCouleur(C1));
    printf("Couleur suivante : %d\n", CouleurSuivante(C1.CC));
    printf("Est-elle cach�e : %d\n", EstCachee(C1));
    printf("Est-elle decouverte : %d\n", EstDecouverte(C1));
}

void testCarteBooleen(Carte C1, Carte C2)
{
printf("C1 est-elle bien de rang inf�rieur � C2 ? : %d\n", RangInferieur(C1, C2));
printf("C1 est-elle de m�me rang que C2 ? : %d\n", MemeRang(C1, C2));
printf("C1 est-elle bien de couleur inf�rieur � C2 ? : %d\n", CouleurInferieure(C1, C2));
printf("C1 est-elle de m�me rang que C2 ? : %d\n", MemeCouleur(C1, C2));
printf("C1 est-elle de rang et couleur inf�rieur � C2 ? : %d\n",EstCarteAvant(C1, C2));
}

void testBoolenTas(Tas T2)
{
printf("Est-ce que le tas est actif ? :\n", TasActif(T2) );
printf("Est-ce que le tas est vide ? :\n", TasVide(T2) );
printf("Est-ce que le tas est empilé ? :\n", TasEmpile(T2) );
printf("Est-ce que le tas est étalé ? :\n", TasEtale(T2) );
}

void testLocalisationPlaceTas(Tas T3)
{
  printf("Est-ce que le tas est empilé ? :\n", LaHauteur(T3) );
  printf("Est-ce que le tas est étalé ? :\n", LaPlace(T3) );
}



/*

CreerTasVide(Localisation L, Mode M, Tas *T);
SupprimerTasVide(Tas *T);
CreerJeuNeuf(int N, Localisation L, Tas *T);

Carte CarteSur(Tas T);
Carte CarteSous(Tas T);
Carte IemeCarte(Tas T, int i);

RetournerCarteSur(Tas *T);
RetournerCarteSous(Tas *T);


EmpilerTas(Tas *T);
EtalerTas(Tas *T);
EchangerCartes(int i, int j, Tas *T);
BattreTas(Tas *T);
RetournerTas(Tas *T);

AjouterCarteSurTas (struct adCarte *ac, Tas *T);
AjouterCarteSousTas (struct adCarte *ac, Tas *T);
DeplacerHautSur(Tas *T1, Tas *T2);
DeplacerHautSous(Tas *T1, Tas *T2);
DeplacerBasSur(Tas *T1, Tas *T2);
DeplacerBasSous(Tas *T1, Tas *T2);
DeplacerCarteSur(Couleur C, Rang R, Tas *T1, Tas *T2);
PoserTasSurTas(Tas *T1, Tas *T2);
*/
