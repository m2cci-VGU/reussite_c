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
	CreerJeuNeuf(32, LocDeck, &deck);
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
SerieCouleur ListeAdresseTasDefausse[NOMBRE_DE_STOCK_MAX];
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
		ListeAdresseTasCouleur[couleur] = adTasVisitor;
	}
	for(index = 0; index < NOMBRE_DE_STOCK_MAX ; index++) {
		adTasVisitor = getTasDefausseMD(index);
		ListeAdresseTasDefausse[index] = adTasVisitor;
	}
}

void runTest() {
	booleen test;
	AfficherMD();
	AttendreCliquer();
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

void test2(){
	newTest("Test 2");
	printf("Vérifier la remontée des cartes du stock vers la ligne de couleur\n");

	ajouterCarteSurTasDeDefausse(0, Trefle, As);
	ajouterCarteSurTasDeDefausse(0, Trefle, Dame);
	ajouterCarteSurTasDeDefausse(0, Trefle, Dix);
	ajouterCarteSurTasDeDefausse(1, Trefle, Roi);
	Tas* adTas = ListeAdresseTasDefausse[1];
	Carte c = CarteSur(*adTas);
	ajouterCarteSurTasDeDefausse(1, Trefle, Valet);
	c = CarteSur(*adTas);
	ajouterCarteSurTasDeDefausse(1, Trefle, Neuf);
	c = CarteSur(*adTas);
	ajouterCarteSurTasDeDefausse(2, Trefle, Huit);

	ajouterCarteSurTalon(Trefle, Sept);

	runTest();
	endTest();

}

void test3(){

	newTest("Test 2");
	printf("Vérifier Une situation de perte de partie\n");
	ajouterCarteSurTasDeDefausse(0, Trefle, As);
	ajouterCarteSurTasDeDefausse(0, Coeur, Roi);
	ajouterCarteSurTasDeDefausse(1, Coeur, Dame);
	ajouterCarteSurTasDeDefausse(2, Pique, Roi);
	ajouterCarteSurTasDeDefausse(3, Trefle, Valet);

	ajouterCarteSurTasDeCouleur(Carreau, Sept);
	ajouterCarteSurTasDeCouleur(Carreau, Huit);
	ajouterCarteSurTasDeCouleur(Coeur, Sept);
	ajouterCarteSurTasDeCouleur(Coeur, Huit);
	ajouterCarteSurTasDeCouleur(Pique, Sept);
	ajouterCarteSurTasDeCouleur(Pique, Huit);
	ajouterCarteSurTasDeCouleur(Trefle, Sept);
	ajouterCarteSurTasDeCouleur(Trefle, Huit);

	ajouterCarteSurTalon(Pique, As);

	runTest();
	endTest();

}

int main() {
	test1();
	test2();
	test3();
}
