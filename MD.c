#include <stdio.h>
#include "MD.h"

char TexteCouleurMD[5][12] = {"", "Trefle", "Carreau", "Coeur", "Pique"};

typedef Tas SerieCouleurMD;
SerieCouleurMD LigneMD[DerniereCouleur+1];
Tas TalonMD, Stock1, Stock2, Stock3, Stock4;
	/* localisation des tas */
Localisation LocSerieMD[DerniereCouleur+1];
Localisation LocTalonMD, LocStock1, LocStock2, LocStock3, LocStock4;

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
        LocSerieMD[i].NC = 2*i+6;
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

void JouerTasMD(Tas *T, booleen *OK)
{
  Couleur Co;
  Rang RT, RSur;

  Co = LaCouleur(CarteSur(*T));
  RT = LeRang(CarteSur(*T));
  RSur = LeRang(CarteSur(LigneMD[Co]));

  *OK = vrai;
  if (RT == 7){
  	DeplacerHautSur(T, &(LigneMD[Co]));
  }
  else if (RT == RangSuivant(RSur)){
  	 DeplacerHautSur(T, &(LigneMD[Co]));
  }
   
  else if (RSous == RangSuivant(RT))
    DeplacerHautSous(T, &(LigneR7[Co]));
  else 
    *OK = faux;
}
