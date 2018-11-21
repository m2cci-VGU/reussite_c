#include <stdio.h>
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
}
/* Bonjour CECI est INUTILE Merci !

void ReformerTableauInitialMD()
{
	Couleur Co;

	if(!TasVide(TalonMD)){
		RetournerTas(&TalonMD);
	}
	if(!TasVide(Stock1)){
		EmpilerTas(&Stock1);
	}
	if(!TasVide(Stock2)){
		EmpilerTas(&Stock2);
	}
	if(!TasVide(Stock3)){
		EmpilerTas(&Stock3);
	}
	if(!TasVide(Stock4)){
		EmpilerTas(&Stock4);
	}
	PoserTasSurTas(&Stock1, &TalonMD);
	PoserTasSurTas(&Stock2, &TalonMD);
	PoserTasSurTas(&Stock3, &TalonMD);
	PoserTasSurTas(&Stock4, &TalonMD);

	for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++)
	{
		EmpilerTas(&(LigneMD[Co]));
		PoserTasSurTas(&(LigneMD[Co]), &TalonMD);
		EtalerTas(&(LigneMD[Co]));
	}
	RetournerTas(&TalonMD);
	BattreTas(&TalonMD);
}
BISOUS */
 
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

	AttendreCliquer();
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

void JouerTasSurStock(Tas* T, booleen* OK){

	Rang RT, RStock1, RStock2, RStock3, RStock4;

	RT = LeRang(CarteSur(*T));



	if(TasVide(Stock1)){
		RStock1=0;
	}
	else {
		RStock1 = LeRang(CarteSur(Stock1));
	}
	if(TasVide(Stock2)){
		RStock2=0;
	}
	else {
		RStock2 = LeRang(CarteSur(Stock2));
	}
	if(TasVide(Stock3)){
		RStock3=0;
	}
	else {
		RStock3 = LeRang(CarteSur(Stock3));
	}
	if(TasVide(Stock4)){
		RStock4=0;
	}
	else {
		RStock4 = LeRang(CarteSur(Stock4));
	}

	*OK = vrai;
	if (!TasVide(Stock1) && RT==RStock1-1){
		DeplacerHautSur(&TalonMD, &Stock1);
	}
	else if (!TasVide(Stock2) && RT==RStock2-1){
		DeplacerHautSur(&TalonMD, &Stock2);
	}
	else if (!TasVide(Stock3) && RT==RStock3-1){
		DeplacerHautSur(&TalonMD, &Stock3);
	}
	else if (!TasVide(Stock4) && RT==RStock4-1){
		DeplacerHautSur(&TalonMD, &Stock4);
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

void RemonterCarteStock(){

	booleen OKStock1 = faux;
	booleen OKStock2 = faux;
	booleen OKStock3 = faux;
	booleen OKStock4 = faux;

	do {
		if(!(TasVide(Stock1))){
			JouerTasSurLigneMD(&Stock1, &OKStock1);
		}
		if(!(TasVide(Stock2))){
			JouerTasSurLigneMD(&Stock2, &OKStock2);
		}
		if(!(TasVide(Stock3))){
			JouerTasSurLigneMD(&Stock3, &OKStock3);
		}
		if(!(TasVide(Stock4))){
			JouerTasSurLigneMD(&Stock4, &OKStock4);
		}
	}
	while (OKStock1 || OKStock2 || OKStock3 || OKStock4);
}

void JouerUneMD(ModeTrace MT){

	booleen poserLigne;
	booleen poserStock;


	InitialisationMD();
	do	{
		RetournerCarteSur(&TalonMD);
		if (MT == AvecTrace){
			AfficherMD();
		}
		JouerTasSurLigneMD(&TalonMD, &poserLigne);
		if (!poserLigne){
			JouerTasSurStock(&TalonMD, &poserStock);
			if (poserStock && MT == AvecTrace){
				AfficherMD();
			}
		}
		if (poserLigne){
			RemonterCarteStock();
			if (MT == AvecTrace){
				AfficherMD();
			}
		}
	}
	while ((poserStock || poserLigne) && !(TasVide(TalonMD)));

	if (TasVide(TalonMD) && (poserStock || poserLigne)){
		printf("Bravo c'est gagné!\n");
	}
	else {
		printf("BUHAHAHAHHAHA t'as perdu, essayes encore !\n");
	}

}

void ObserverMD(int NP)
{
	int i;

	CreerTableauInitialMD();
	JouerUneMD(AvecTrace);
	for (i = 1; i <= NP-1; i++)
	{
		CreerTableauInitialMD();
		JouerUneMD(AvecTrace);
	}
}

void AnalyserMD(int NP)
{
	/* A COMPLETER */
}
