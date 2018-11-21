#include <stdio.h>
#include <stdlib.h>
#include "R7.h"

//////// Independant du jeu /////////////

void initTestDeck() {
  Localisation LocDeck;
  LocDeck.NC = 42;
  LocDeck.NL = 42;
  CreerJeuNeuf(52, LocDeck, &deck);
}
void initTas(Tas* adTas) {
  SupprimerTasVide(adTas);
  CreerTasVide(LaPlace(*adTas), TasEtale(*adTas), adTas);
}
initTestEnvironment(char* testName) {
    initTestDeck();
    InitAlea();
    OuvrirGraphique(testName);
}
void endTest() {
  FermerGraphique();
}

////////////////////////////////////////////////////////
// Specifiques au jeu: tas disponibles, et fonctions //
//////////////////////////////////////////////////////

Tas deck;
typedef Tas* SerieCouleur;
SerieCouleur ListeAdresseTasCouleur[DerniereCouleur+1];
Tas *adTalon, *adRebut;

void newTest(char* testName)
{
  initTestEnvironment(testName);

  CreerTableauInitialR7();

  adTalon = getTalonR7();
  adRebut = getRebutR7();

  initTas(adTalon);
  initTas(adRebut);

  Tas* adTasVisitor;
  for(int couleur=PremiereCouleur; couleur<DerniereCouleur+1 ; couleur++) {
    adTasVisitor = getTasCouleurR7(couleur);
    initTas(adTasVisitor);
    ListeAdresseTasCouleur[couleur] = adTasVisitor;
  }
}

void runTest() {
  JouerUneR7(1, AvecTrace);
}

  ////////////////////////////////////////////////////////////
 // Fonctions spécifiques (inutiles mais qui simplifient les tests) //
///////////////////////////////////////////////////////////

void ajouterCarteSurTasDeCouleur(Couleur couleur, Rang rang) {
  Tas* adDest = ListeAdresseTasCouleur[couleur];
  DeplacerCarteSur(couleur, rang, &deck, adDest);
  RetournerCarteSur(adDest);
}

void ajouterCarteSurTalon(Couleur couleur, Rang rang) {
  DeplacerCarteSur(couleur, rang, &deck, adTalon);
}

void ajouterCarteSurRebut(Couleur couleur, Rang rang) {
  DeplacerCarteSur(couleur, rang, &deck, adRebut);
  RetournerCarteSur(adRebut);
}

void ajouterFamilleSurTalon(Rang rang) {
  ajouterCarteSurTalon(Coeur, rang);
  ajouterCarteSurTalon(Pique, rang);
  ajouterCarteSurTalon(Trefle, rang);
  ajouterCarteSurTalon(Carreau, rang);
}


////////////////
//// Tests ////
//////////////

void test1() {
    newTest("Test 1");
    printf("Principe de ce test: verifier que ca marche\n");
    ajouterCarteSurTasDeCouleur(Trefle, Deux);
    ajouterCarteSurTasDeCouleur(Carreau, Trois);
    ajouterCarteSurTasDeCouleur(Coeur, Quatre);
    ajouterCarteSurTasDeCouleur(Pique, Cinq);
    ajouterCarteSurTalon(Coeur, Roi);
    ajouterFamilleSurTalon(Dame);
    ajouterCarteSurRebut(Trefle, Cinq);

    runTest();
    endTest();
}

int main() {
  test1();
}
