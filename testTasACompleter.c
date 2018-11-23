#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TasACompleter.h"

int main()
{
  void afficherTasPourTest(Tas T);
  void afficherCarte(Carte C);
  void testCarte(Carte C1);
  void testCarteBooleen(Carte C1, Carte C2);
  void testTas(Tas T);
  /*TAS*/
  Tas T1;
  Tas T2;

  int N = 52;
  Localisation L;
  L.NL = 1 ;
  L.NC = 1 ;

  Tas T3;
  int N1 = 52;
  Localisation L1;
  L1.NL = 1 ;
  L1.NC = 1 ;
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
  struct adCarte C1struct;
  C1struct.elt=C1;

  Carte C2;
  C2.RC = Valet;
  C2.CC = Pique;
  C2.VC = Cachee;
  struct adCarte C2struct;
  C2struct.elt=C2;


  /*afficherCarte(C1);
  afficherCarte(C2);
  testCarte(C1);
  testCarteBooleen(C1, C2);*/

  /*CreerJeuNeuf(N1, L1, &T1);
  afficherTasPourTest(T1);
  RetournerTas(&T1);
  afficherTasPourTest(T1);*/



  //testBoolenTas(T1);
  //  testLocalisationPlaceTas(T1);



  CreerTasVide(L,etale,&T2); afficherTasPourTest(T2); testTas(T2);
  SupprimerTasVide(&T2); afficherTasPourTest(T2); testTas(T2);
  CreerJeuNeuf(N,L,&T2);  afficherTasPourTest(T2); testTas(T2);
  EchangerCartes(1,2,&T2);EchangerCartes(51,52,&T2); EchangerCartes(26,27,&T2);  afficherTasPourTest(T2);
  BattreTas(&T2);  afficherTasPourTest(T2); testTas(T2);
  EmpilerTas(&T2); testTas(T2);
  EtalerTas(&T2); testTas(T2);
  printf("\ntest retournement tas ou cartes\n");
  CreerTasVide(L,etale,&T1);CreerJeuNeuf(N1, L1, &T1); printf("\nTas de depart \n");afficherTasPourTest(T1); testTas(T1);
  RetournerTas(&T1);  afficherTasPourTest(T1);testTas(T1);
  printf("\ntest deplacement cartes d'un Tas à l'autre\n");
  CreerTasVide(L,etale,&T1);CreerJeuNeuf(N1, L1, &T1);CreerTasVide(L,etale,&T2);CreerJeuNeuf(N,L,&T2);  printf("\nTas de depart 1\n");afficherTasPourTest(T1); testTas(T1);  printf("\nTas de depart 2\n");afficherTasPourTest(T2);testTas(T2);
  printf("\ntest deplacerHautSur-T2 recoit en queue la queue de T1\n");
  DeplacerHautSur(&T1,&T2); afficherTasPourTest(T1);printf("\nLahauteur du Tas est %d\n",LaHauteur(T1));afficherTasPourTest(T2);printf("\nLahauteur du Tas est %d\n",LaHauteur(T2));
  printf("\ntest deplacerHautSous-T2 recoit en tete la queue de T1\n");
  DeplacerHautSous(&T1,&T2); afficherTasPourTest(T1);printf("\nLahauteur du Tas est %d\n",LaHauteur(T1));afficherTasPourTest(T2);printf("\nLahauteur du Tas est %d\n",LaHauteur(T2));
  printf("\ntest DeplacerBasSur-T2 recoit en queue la tete de T1\n");
  DeplacerBasSur(&T1,&T2); afficherTasPourTest(T1);printf("\nLahauteur du Tas est %d\n",LaHauteur(T1));afficherTasPourTest(T2);printf("\nLahauteur du Tas est %d\n",LaHauteur(T2));
  printf("\ntest DeplacerBasSous-T2 recoit en tete la tete de T1\n");
  DeplacerBasSous(&T1,&T2); afficherTasPourTest(T1);printf("\nLahauteur du Tas est %d\n",LaHauteur(T1));afficherTasPourTest(T2);printf("\nLahauteur du Tas est %d\n",LaHauteur(T2));
  printf("\ntest DeplacerCarteSur-la carte de couleur C et rang R de T1 est placée en queue de T2\n");
  CreerTasVide(L,etale,&T1);CreerJeuNeuf(N1, L1, &T1);CreerTasVide(L,etale,&T2);CreerJeuNeuf(N,L,&T2);  printf("\nTas de depart 1\n");afficherTasPourTest(T1); testTas(T1);  printf("\nTas de depart 2\n");afficherTasPourTest(T2);testTas(T2);
  DeplacerCarteSur(2,14,&T1,&T2);afficherTasPourTest(T1);printf("\nLahauteur du Tas est %d\n",LaHauteur(T1));afficherTasPourTest(T2);printf("\nLahauteur du Tas est %d\n",LaHauteur(T2));
  printf("\ntest PoserTasSurTas-T2 recoit toutes sur sa queue les cartes de T1, qui restent en ordre. T1 devient vide\n");
  PoserTasSurTas(&T1,&T2);afficherTasPourTest(T1);printf("\nLahauteur du Tas est %d\n",LaHauteur(T1));afficherTasPourTest(T2);printf("\nLahauteur du Tas est %d\n",LaHauteur(T2));
  /*printf("\ntest ajout cartes cartes\n");
  CreerTasVide(L,etale,&T1);CreerJeuNeuf(N1, L1, &T1);afficherTasPourTest(T1);
  printf("la carte ajoutee sera\n[%d %d %d]",C1struct.elt.RC,C1struct.elt.CC,C1struct.elt.VC);
  AjouterCarteSurTas(&C1struct,&T1);afficherTasPourTest(T1); testTas(T1);
  AjouterCarteSousTas(&C1struct,&T1);afficherTasPourTest(T1); testTas(T1);*/

  return 0;
}



void afficherTasPourTest(Tas T)
{
  struct adCarte *visiteur = T.tete;

  printf("Le TAS est [ ") ;
  int k=1;
  while (k <= T.HT && visiteur != NULL)
  {
    printf("%d%d%d ", visiteur->elt.RC, visiteur->elt.CC, visiteur->elt.VC) ;
    visiteur = visiteur->suiv;
    k++;
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
  printf("C1 est-elle bien de rang inf�rieur � C2 ?\n : %d", RangInferieur(C1, C2));
  if (MemeRang(C1,C2)) {printf("\nC1 et C2 ont le meme rang");
}
else {printf("\nC1 et C2 n'ont pas le meme rang");
}
printf("C1 est-elle bien de couleur inf�rieur � C2 ?\n : %d", CouleurInferieure(C1, C2));
printf("C1 est-elle de m�me rang que C2 ?\n : %d", MemeCouleur(C1, C2));
printf("C1 est-elle de rang et couleur inf�rieur � C2 ?\n : %d",EstCarteAvant(C1, C2));
}

void testTas(Tas T)
{
  if (TasActif(T)) {printf("Le tas est actif");
}
else {printf("\nLe tas est inactif");
}
if (TasVide(T)) {printf("\nLe tas est vide");
}
else {printf("\nLe tas n'est pas vide");
}
if (TasEmpile(T)) {printf("\nLe tas est empile");
}
else {printf("\nLe tas n'est pas empile");
}
if (TasEtale(T)) {printf("\nLe tas est etale");
}
else {printf("\nLe tas n'est pas etale");
}
printf("\nLahauteur du Tas est %d",LaHauteur(T));
printf("\nLa localisation du tas est %d,%d\n",T.LT.NC, T.LT.NL);

if (T.HT != 0)
{
  Carte cartesur=CarteSur(T); Carte cartesous=CarteSous(T);int i = 51; Carte carteI=IemeCarte(T,i);
  printf("\nla premiere carte est [%d %d %d]",cartesur.RC,cartesur.CC,cartesur.VC);
  printf("\nla derniere carte est [%d %d %d]",cartesous.RC,cartesous.CC,cartesous.VC);
  printf("\nla carte numero %d est [%d %d %d]",i, carteI.RC,carteI.CC,carteI.VC);
}
}
/*printf("C1 est-elle bien de rang inf�rieur � C2 ? : %d\n", RangInferieur(C1, C2));
printf("C1 est-elle de m�me rang que C2 ? : %d\n", MemeRang(C1, C2));
printf("C1 est-elle bien de couleur inf�rieur � C2 ? : %d\n", CouleurInferieure(C1, C2));
printf("C1 est-elle de m�me rang que C2 ? : %d\n", MemeCouleur(C1, C2));
printf("C1 est-elle de rang et couleur inf�rieur � C2 ? : %d\n",EstCarteAvant(C1, C2));*/

/*void testBoolenTas(Tas T2)
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
}*/

/*



fonctions a tester - marco jeudi 17h00

RetournerCarteSur(Tas *T);
RetournerCarteSous(Tas *T);
RetournerTas(Tas *T);         xxx à verifier la visibilité

*/
