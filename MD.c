#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "MD.h"
#include <unistd.h>

char TexteCouleurMD[5][8] = {"", "Trefle", "Carreau", "Coeur", "Pique"};

typedef Tas SerieCouleurMD;
SerieCouleurMD LigneMD[DerniereCouleur+1];
SerieCouleurMD tasStock[NOMBRE_DE_STOCK];
Tas TalonMD;
/* localisation des tas */
Localisation LocSerieMD[DerniereCouleur+1];
Localisation LocTasStock[NOMBRE_DE_STOCK];
Localisation LocTalonMD;

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
	return &(tasStock[index]);
}


void SaisirLocTasMD() {
	int i;
	for(i = 0; i < NOMBRE_DE_STOCK; i++) {
		LocTasStock[i].NC = i+1;
		LocTasStock[i].NL = 1;
	}
	LocTalonMD.NC = NOMBRE_DE_STOCK+1;
	LocTalonMD.NL = 3;
	for (i=PremiereCouleur; i<=DerniereCouleur; i++)
	{
		LocSerieMD[i].NC = i+NOMBRE_DE_STOCK+1;
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
	int i;

	SaisirLocTasMD();
	/* Création du talon avec un jeu de 32 cartes et des différents stocks */
	CreerJeuNeuf(32, LocTalonMD, &TalonMD);
	BattreTas(&TalonMD);
	for(i=0; i<NOMBRE_DE_STOCK; i++) {
		CreerTasVide(LocTasStock[i], etale, &(tasStock[i]));
	}
	/* Création des séries de chaque couleur */
	for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++)	{
		CreerTasVide(LocSerieMD[Co], etale, &(LigneMD[Co]));
	}
	InitialisationMD();
}

void AfficherMD( )
{
	Couleur Co;
	int i;

	EffacerGraphique();
	AfficherTas(TalonMD, "Talon");
	for(i=0; i<NOMBRE_DE_STOCK; i++) {
		AfficherTas(tasStock[i], "Stock");
	}
	for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++) {
		AfficherTas(LigneMD[Co], TexteCouleurMD[Co]);
		/* AttendreCliquer(); */
	}
	usleep(temps);
}
void JouerTasSurLigneMD(Tas *T, booleen *OK){
	Couleur Co = VideC;
	Rang RT=0, RSur=0;

	if( !TasVide(*T) ) {
		Co = LaCouleur(CarteSur(*T));
		RT = LeRang(CarteSur(*T));
		RSur = LeRang(CarteSur(LigneMD[Co]));
	}

	*OK = faux;
	if (RT !=0 && RT == RangSuivant(RSur)){
		*OK = vrai;
		DeplacerHautSur(T, &(LigneMD[Co]));
	}
}
/* Fonction qui trouve l ecart minimum entre les stocks et la pioche, retourne le stock concerne*/

void TrouverMeilleureCible (Rang RPioche, Tas** Cible, int* OK){
	int i;
	Rang rangTas;
	int ecartMax = As+1;
	Rang rangCaseVide = ecartMax;
	int ecartTas, ecartMin = ecartMax;

	/* printf("-------------TrouverMeilleurTas-----------\n"); */
	/* printf("Rang de la carte a poser: %d\n", RPioche); */
	for(i=0; i<NOMBRE_DE_STOCK; i++) {
		rangTas = TasVide(tasStock[i]) ? rangCaseVide : LeRang(CarteSur(tasStock[i]));
		ecartTas = (RPioche > rangTas) ? ecartMax : (rangTas - RPioche);
		/*printf(" - tas %d || rang: %d || ecart: %d\n", i, rangTas, ecartTas);*/
		*Cible = (ecartTas < ecartMin) ? &(tasStock[i]) : *Cible;
		ecartMin = (ecartTas < ecartMin) ? ecartTas : ecartMin;
	}
	/* printf("FIN: ecartMin=%d <-> ecartMax=%d\n",ecartMin, ecartMax)	; */
	*OK = (ecartMin < ecartMax);
}

void JouerTasSurStock(Tas* T, booleen* carteDeplacee){
	Tas* Cible;
	booleen foundBestTarget;

	Rang RT = LeRang(CarteSur(*T));
	TrouverMeilleureCible(RT,&Cible,&foundBestTarget);

	if (foundBestTarget){
		*carteDeplacee = vrai;
		DeplacerHautSur(&TalonMD, Cible);
	} else {
		*carteDeplacee = faux;
	}
}

void RemonterCarteStock(ModeTrace MT){
	booleen carteDeplacee = faux;
	int i;
	do {
		carteDeplacee = faux;
		for(i=0 ; i<NOMBRE_DE_STOCK ; i++) {
			JouerTasSurLigneMD( &(tasStock[i]), &carteDeplacee);
			if (carteDeplacee){
				break;
				if(MT == AvecTrace){
					AfficherMD();
				}
			}
		}
	}	while (carteDeplacee);
}

void StockVide(booleen* vide){
	
	int i =0;
	*vide = faux;
	while (i<NOMBRE_DE_STOCK && TasVide(tasStock[i])){
		i++;
	}
	if (i==NOMBRE_DE_STOCK){
		*vide = vrai;
	}
}

void JouerUneMD(ModeTrace MT, booleen* Victoire){

	booleen poserLigne;
	booleen poserStock;
	booleen vide;

	do	{
		RetournerCarteSur(&TalonMD);
		/*Carte c = CarteSur(TalonMD);*/
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
		else {
			poserStock = faux;
			RemonterCarteStock(MT);
			if (MT == AvecTrace){
				AfficherMD();
			}
		}
		/* printf("Carte: %d de %d\n", c.RC, c.CC);
		printf("Placer sur stock: %d\n", poserStock);
		printf("Placer sur ligne: %d\n", poserLigne);
		printf("TasVide: %d\n",TasVide(TalonMD));
		printf("Sortie du while: %s\n\n", (poserStock || poserLigne) && !(TasVide(TalonMD)) ? "non" : "oui");
		*/
	}	while ((poserStock || poserLigne) && !(TasVide(TalonMD)));
	if (TasVide(TalonMD)){
		RemonterCarteStock(MT);
		StockVide(&vide);
		if (vide){
			if (MT == AvecTrace){
				printf("Bravo c'est gagné!\n");
			}
			*Victoire=vrai;
		}
		else {
			printf("BUHAHAHAHHAHA t'as perdu, essayes encore !\n");
		}
	}
	else {
		if (MT == AvecTrace){
			printf("BUHAHAHAHHAHA t'as perdu, essayes encore !\n");
		}
		*Victoire=faux;
	}

}

void ObserverMD(int NP)
{
	booleen gagne;
	int i;
	for (i = 0; i <= NP-1; i++)
	{
		CreerTableauInitialMD();
		JouerUneMD(AvecTrace,&gagne);
	}
}

void AnalyserMD(int NP)
{
	int i;
	int victoire = 0;
	float michel;
	booleen gagne;

	for (i = 0; i < NP ; i++){
		CreerTableauInitialMD();
		JouerUneMD(SansTrace, &gagne);
		if (gagne){
			victoire++;
		}
	}
	michel = (float)victoire/NP;
	printf("Sur %d parties vous avez eu de la chance %d fois et manqué de bol %d fois (bah oui t as pas fait grand chose)\n", NP,victoire,(NP-victoire));
	printf("Vous avez un taux de victoire de %.2f%% \n", michel*100);
}
