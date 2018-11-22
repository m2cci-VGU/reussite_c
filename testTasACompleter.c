#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TasACompleter.h"

int main()
{
    /*TAS*/
        Tas T;
        Tas T1;
        Tas T2;
        int N = 52;
        Localisation L;
        L.NL = 1 ;
        L.NC = 1 ;
        char message;

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

    afficherCarte(C);
    afficherCarte(C1);
    afficherCarte(C2);

    testCarte(C1);
    testCarteBooleen(C1, C2);


};


/*void testMouvementCarteTas(T)
{
    CreerJeuNeuf(N, L, *T);
    afficherTasPourTest(T);
    AjouterCarteSurTas (struct adCarte *ac, Tas *T)
    afficherPremiereCarteAccessible(*T);
    afficherTasPourTest(T);
}*/

/*
AjouterCarteSurTas (struct adCarte *ac, Tas *T);
AjouterCarteSousTas (struct adCarte *ac, Tas *T);
DeplacerHautSur(Tas *T1, Tas *T2);
DeplacerHautSous(Tas *T1, Tas *T2);
DeplacerBasSur(Tas *T1, Tas *T2);
DeplacerBasSous(Tas *T1, Tas *T2);
DeplacerCarteSur(Couleur C, Rang R, Tas *T1, Tas *T2);
PoserTasSurTas(Tas *T1, Tas *T2);
*/


void afficherTasPourTest(Tas T)
{
    struct adCarte *visiteur = T.tete;

    printf("Le TAS est [ ") ;
    while (visiteur != NULL)
    {
        printf("%d%d%s ", visiteur->elt.RC, visiteur->elt.CC, visiteur->elt.VC) ;
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
    printf("Est-elle cachée : %d\n", EstCachee(C1));
    printf("Est-elle decouverte : %d\n", EstDecouverte(C1));
}

void testCarteBooleen(Carte C1, Carte C2)
{
printf("C1 est-elle bien de rang inférieur à C2 ?\n : %d", RangInferieur(C1, C2));
printf("C1 est-elle de même rang que C2 ?\n : %d", MemeRang(C1, C2));
printf("C1 est-elle bien de couleur inférieur à C2 ?\n : %d", CouleurInferieure(C1, C2));
printf("C1 est-elle de même rang que C2 ?\n : %d", MemeCouleur(C1, C2));
printf("C1 est-elle de rang et couleur inférieur à C2 ?\n : %d",EstCarteAvant(C1, C2));
}





/*
booleen TasActif(Tas T);
booleen TasVide(Tas T);
booleen TasEmpile(Tas T);
booleen TasEtale(Tas T);
LaHauteur(Tas T);
Localisation LaPlace(Tas T);


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




