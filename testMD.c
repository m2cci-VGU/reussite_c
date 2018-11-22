#include <stdio.h>
#include <stdlib.h>
#include "MD.h"
#include "Alea.h"

//////// Independant du jeu /////////////

Tas deck;
typedef Tas* SerieCouleur;

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
void initTestEnvironment(char* testName) {
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

SerieCouleur ListeAdresseTasCouleur[DerniereCouleur+1];
SerieCouleur ListeAdresseTasDefausse[NOMBRE_DE_STOCK];
Tas *adTalon;

void newTest(char* testName)
{
	initTestEnvironment(testName);
	Couleur couleur;
	int index;
	CreerTableauInitialMD();
	adTalon = getTalonMD();
	initTas(adTalon);

	Tas* adTasVisitor;
	for(couleur=PremiereCouleur; couleur<DerniereCouleur+1 ; couleur++) {
		adTasVisitor = getTasCouleurMD(couleur);
		initTas(adTasVisitor);
		ListeAdresseTasCouleur[couleur] = adTasVisitor;
	}
	for(index = 0; index < NOMBRE_DE_STOCK ; index++) {
		adTasVisitor = getTasDefausseMD(index);
		initTas(adTasVisitor);
		ListeAdresseTasDefausse[index] = adTasVisitor;
	}
}

void runTest() {
	booleen test;
	JouerUneMD(AvecTrace, &test);
}

/////////////////////////////////////////////////////////////////////
// Fonctions spécifiques (inutiles mais qui simplifient les tests) //
/////////////////////////////////////////////////////////////////////

void ajouterCarteSurTasDeCouleur(Couleur couleur, Rang rang) {
	Tas* adDest = ListeAdresseTasCouleur[couleur];
	DeplacerCarteSur(couleur, rang, &deck, adDest);
	RetournerCarteSur(adDest);
}
void ajouterCarteSurTasDeDefausse(int i, Couleur couleur, Rang rang) {
	Tas* adDest = ListeAdresseTasDefausse[i];
	DeplacerCarteSur(couleur, rang, &deck, adDest);
	RetournerCarteSur(adDest);
}

void ajouterCarteSurTalon(Couleur couleur, Rang rang) {
	DeplacerCarteSur(couleur, rang, &deck, adTalon);
}

void ajouterFamilleSurTalon(Rang rang) {
	ajouterCarteSurTalon(Coeur, rang);
	ajouterCarteSurTalon(Pique, rang);
	ajouterCarteSurTalon(Trefle, rang);
	ajouterCarteSurTalon(Carreau, rang);
}


///////////////
/// Tests ////
//////////////

void test1() {
	newTest("Test 1");
	printf("Principe de ce test: verifier que ca marche\n");
	// ajouterCarteSurTasDeCouleur(Pique, Sept);

	ajouterCarteSurTasDeDefausse(0, Trefle, Huit);
	ajouterCarteSurTasDeDefausse(1, Trefle, Dame);
	ajouterCarteSurTasDeDefausse(1, Trefle, Dix);

	ajouterCarteSurTalon(Trefle, Sept);

	runTest();
	endTest();
}

int main() {
	test1();
}
