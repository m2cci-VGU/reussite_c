#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "MD.h"


char TexteCouleurMD[5][8] = {"", "Trefle", "Carreau", "Coeur", "Pique"};

typedef Tas SerieCouleurMD;
SerieCouleurMD LigneMD[DerniereCouleur+1];
Tas TalonMD, Stock1, Stock2, Stock3, Stock4;
/* localisation des tas */
Localisation LocSerieMD[DerniereCouleur+1];
Localisation LocTalonMD, LocStock1, LocStock2, LocStock3, LocStock4;

Carte SixTrefle;
Carte SixCarreau;
Carte SixCoeur;
Carte SixPique;

struct adCarte adSixTrefle;
struct adCarte adSixCarreau;
struct adCarte adSixCoeur;
struct adCarte adSixPique;



Tas* getTalonMD() {
	return &TalonMD;
}
Tas* getTasCouleurMD(Couleur couleur){
	return &(LigneMD[couleur]);
}
Tas* getTasDefausseMD(int index) {
	switch(index){
		case 0: return &Stock1;
		case 1: return &Stock2;
		case 2: return &Stock3;
		case 3: return &Stock4;
		default: return NULL;
	}
}


void SaisirLocTasMD() {
	int i;

	LocTalonMD.NC = 5;
	LocTalonMD.NL = 3;
	LocStock1.NC = 1;
	LocStock1.NL = 1;
	LocStock2.NC = 2;
	LocStock2.NL = 1;
	LocStock3.NC = 3;
	LocStock3.NL = 1;
	LocStock4.NC = 4;
	LocStock4.NL = 1;

	for (i=PremiereCouleur; i<=DerniereCouleur; i++)
	{
		LocSerieMD[i].NC = i+5;
		LocSerieMD[i].NL = 1;
	}
}

/* Créer une carte invisible de Rang Six et de couleur donnée. Créer une structure adresse pour cette carte et fixe le précédent et le suivant à NULL*/
void CreerCarteFictiveMD(Carte* carteFictive, Couleur V, struct adCarte* adCarteFictive){

	carteFictive->CC= V;
	carteFictive->RC= Six;
	carteFictive->VC= Cachee;

	adCarteFictive->elt= *carteFictive;
	adCarteFictive->suiv=NULL;
	adCarteFictive->prec=NULL;
}

void InitialisationMD(){

	CreerCarteFictiveMD(&SixTrefle, Trefle, &adSixTrefle);
	AjouterCarteSurTas(&adSixTrefle, &LigneMD[1]);
	CreerCarteFictiveMD(&SixCarreau, Carreau, &adSixCarreau);
	AjouterCarteSurTas(&adSixCarreau, &LigneMD[2]);
	CreerCarteFictiveMD(&SixCoeur, Coeur, &adSixCoeur);
	AjouterCarteSurTas(&adSixCoeur, &LigneMD[3]);
	CreerCarteFictiveMD(&SixPique, Pique, &adSixPique);
	AjouterCarteSurTas(&adSixPique, &LigneMD[4]);

}

void CreerTableauInitialMD()
{
	Couleur Co;

	SaisirLocTasMD();

	/* Création du talon avec un jeu de 32 cartes et des différents stocks */
	CreerJeuNeuf(32, LocTalonMD, &TalonMD);
	BattreTas(&TalonMD);
	CreerTasVide(LocStock1, etale, &Stock1);
	CreerTasVide(LocStock2, etale, &Stock2);
	CreerTasVide(LocStock3, etale, &Stock3);
	CreerTasVide(LocStock4, etale, &Stock4);

	/* Création des séries de chaque couleur */

	for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++)
	{
		CreerTasVide(LocSerieMD[Co], etale, &(LigneMD[Co]));
	}

	InitialisationMD();
}

void AfficherMD()
{
	Couleur Co;

	EffacerGraphique();
	AfficherTas(TalonMD, "Talon");
	AfficherTas(Stock1, "Stock");
	AfficherTas(Stock2, "Stock");
	AfficherTas(Stock3, "Stock");
	AfficherTas(Stock4, "Stock");

	for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++)
		AfficherTas(LigneMD[Co], TexteCouleurMD[Co]);

	/* AttendreCliquer(); */
}

void JouerTasSurLigneMD(Tas *T, booleen *OK){
	Couleur Co;
	Rang RT, RSur;

	if (TasVide(*T)){
		Co=VideC;
	}
	else {
		Co = LaCouleur(CarteSur(*T));
	}

	if (TasVide(*T)){
		RT=0;
	}
	else {
		RT = LeRang(CarteSur(*T));
	}
	if (TasVide(LigneMD[Co])){
		RSur=0;
	}
	else {
		RSur = LeRang(CarteSur(LigneMD[Co]));
	}

	*OK = vrai;

	if (RT !=0 && RT == RangSuivant(RSur)){
		DeplacerHautSur(T, &(LigneMD[Co]));
	}
	else{
		*OK = faux;
	}
}
/* Fonction qui trouve l ecart minimum entre les stocks et la pioche, retourne le stock concerne*/

void TrouverEcartMinimum (Rang RPioche, Tas** Cible, booleen* OK){
	Rang RStock1, RStock2, RStock3, RStock4, E1, E2, E3, E4, Min;
	int i;
	*OK = vrai;
	RStock1 = TasVide(Stock1) ? 0 : LeRang(CarteSur(Stock1));
	RStock2 = TasVide(Stock2) ? 0 : LeRang(CarteSur(Stock2));
	RStock3 = TasVide(Stock3) ? 0 : LeRang(CarteSur(Stock3));
	RStock4 = TasVide(Stock4) ? 0 : LeRang(CarteSur(Stock4));

	E1 = (RPioche > RStock1) ? 100 : (RStock1 - RPioche);
	E2 = (RPioche > RStock2) ? 100 : (RStock2 - RPioche);
	E3 = (RPioche > RStock3) ? 100 : (RStock3 - RPioche);
	E4 = (RPioche > RStock4) ? 100 : (RStock4 - RPioche);
	Min = E1;
	*Cible = &Stock1;
	Tas* tabStock[4];
	tabStock[0] = &Stock1;
	tabStock[1] = &Stock2;
	tabStock[2] = &Stock3;
	tabStock[3] = &Stock4;
	Rang tabEcart[4];
	tabEcart[0] = E1;
	tabEcart[1] = E2;
	tabEcart[2] = E3;
	tabEcart[3] = E4;

	for (i=1;i<=3;i++){
		if (Min > tabEcart[i]){
			Min = tabEcart[i];
			*Cible = (tabStock[i]);
		}
	}
	if (Min==100){
		*OK= faux;
	}
}
void JouerTasSurStock(Tas* T, booleen* OK){

	Rang RT;
	Tas* Cible;
	booleen ecart;

	RT = LeRang(CarteSur(*T));
	TrouverEcartMinimum(RT,&Cible,&ecart);

	*OK = vrai;
	if (ecart){
		DeplacerHautSur(&TalonMD, Cible);
	}
	else if (TasVide(Stock1)){
		DeplacerHautSur(&TalonMD, &Stock1);
	}
	else if (TasVide(Stock2)){
		DeplacerHautSur(&TalonMD, &Stock2);
	}
	else if (TasVide(Stock3)){
		DeplacerHautSur(&TalonMD, &Stock3);
	}
	else if (TasVide(Stock4)){
		DeplacerHautSur(&TalonMD, &Stock4);
	}
	else {
		*OK= faux;
	}
}

void RemonterCarteStock(ModeTrace MT){

	booleen OKStock1 = faux;
	booleen OKStock2 = faux;
	booleen OKStock3 = faux;
	booleen OKStock4 = faux;

	do {
		if(!(TasVide(Stock1))){
			JouerTasSurLigneMD(&Stock1, &OKStock1);
			if (OKStock1 && MT == AvecTrace){
				AfficherMD();
				usleep(1000000);
			}
		}
		else {
			OKStock1 = faux;
		}
		if(!(TasVide(Stock2))){
			JouerTasSurLigneMD(&Stock2, &OKStock2);
			if (OKStock2 && MT == AvecTrace){
				AfficherMD();
				usleep(1000000);
			}
		}
		else {
			OKStock2 = faux;
		}
		if(!(TasVide(Stock3))){
			JouerTasSurLigneMD(&Stock3, &OKStock3);
			if (OKStock3 && MT == AvecTrace){
				AfficherMD();
				usleep(1000000);
			}
		}
		else {
			OKStock3 = faux;
		}
		if(!(TasVide(Stock4))){
			JouerTasSurLigneMD(&Stock4, &OKStock4);
			if (OKStock4 && MT == AvecTrace){
				AfficherMD();
				usleep(1000000);
			}
		}
		else {
			OKStock4 = faux;
		}
	}
	while (OKStock1 || OKStock2 || OKStock3 || OKStock4);
}

void JouerUneMD(ModeTrace MT){

	booleen poserLigne;
	booleen poserStock;


	do	{
		RetournerCarteSur(&TalonMD);
		if (MT == AvecTrace){
			AfficherMD();
		}
		/*AttendreCliquer();*/
		usleep(1000000);
		JouerTasSurLigneMD(&TalonMD, &poserLigne);
		if (!poserLigne){
			JouerTasSurStock(&TalonMD, &poserStock);
			if (poserStock && MT == AvecTrace){
				AfficherMD();
			}
		}
		else {
			poserStock = faux;
			RemonterCarteStock(MT);
			if (MT == AvecTrace){
				AfficherMD();
			}
		}
		printf("%d,%d,%d\n",poserStock,poserLigne,!(TasVide(TalonMD)));
	}	while ((poserStock || poserLigne) && !(TasVide(TalonMD)));

	if (TasVide(TalonMD)){
		printf("Bravo c'est gagné!\n");
	}
	else {
		printf("BUHAHAHAHHAHA t'as perdu, essayes encore !\n");
	}

}

void ObserverMD(int NP)
{
	int i;
	for (i = 0; i <= NP-1; i++)
	{
		CreerTableauInitialMD();
		JouerUneMD(AvecTrace);
	}
}

void AnalyserMD(int NP)
{
	/* A COMPLETER */
}
