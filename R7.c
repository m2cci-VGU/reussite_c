/*--------------------------------------------------------------*/
/* Reussites. Michel Bonin, Catherine Parent, octobre 2005,
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

/* Le relais des 7 */

#include <stdio.h>
#include <unistd.h>

#include "R7.h"

char TexteCouleurR7[5][8] = {"", "Trefle", "Carreau", "Coeur", "Pique"};

/* Tableau de jeu */

int NumTourR7;
typedef Tas SerieCouleurR7;
SerieCouleurR7 LigneR7[DerniereCouleur+1];
Tas TalonR7, RebutR7;
	/* localisation des tas */
Localisation LocSeriesR7[DerniereCouleur+1];
Localisation LocTalonR7, LocRebutR7;

/* Formation du tableau de jeu initial */

Tas* getTalonR7 () {
  return &TalonR7;
}
Tas* getRebutR7 () {
  return &RebutR7;
}
Tas* getTasCouleurR7(Couleur Co) {
  return &(LigneR7[Co]);
}

void SaisirLocTasR7()
{
  int i;

  LocTalonR7.NC = 1;
  LocTalonR7.NL = 1;
  LocRebutR7.NC = 1;
  LocRebutR7.NL = 3;

  for (i=PremiereCouleur; i<=DerniereCouleur; i++)
    {
      LocSeriesR7[i].NC = 2*i+2;
      LocSeriesR7[i].NL = 1;
    }
}

void CreerTableauInitialR7()
{
  Couleur Co;

  SaisirLocTasR7();
  NumTourR7 = 1;

  /* Cr�ation du talon avec un jeu de 52 cartes et du rebut avec un tas vide */
  CreerJeuNeuf(52, LocTalonR7, &TalonR7);
  BattreTas(&TalonR7);
  CreerTasVide(LocRebutR7, empile, &RebutR7);

  /* Cr�ation des s�ries de chaque couleur et initialisation avec le sept */

  for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++)
    {
      CreerTasVide(LocSeriesR7[Co], etale, &(LigneR7[Co]));
      DeplacerCarteSur(Co, Sept, &TalonR7, &(LigneR7[Co]));
      RetournerCarteSur(&(LigneR7[Co]));
    }
}

void ReformerTableauInitialR7()
{
  Couleur Co;

  /* On reforme le talon, en empilant les cartes du rebut et de la ligne */
  PoserTasSurTas(&RebutR7, &TalonR7);
  for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++)
    {
      EmpilerTas(&(LigneR7[Co]));
      PoserTasSurTas(&(LigneR7[Co]), &TalonR7);
      EtalerTas(&(LigneR7[Co]));
    }
  RetournerTas(&TalonR7);
  BattreTas(&TalonR7);

  NumTourR7 = 1;

  /* Initialisation des s�ries de chaque couleur avec le sept */

  for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++)
    {
      DeplacerCarteSur(Co, Sept, &TalonR7, &(LigneR7[Co]));
      RetournerCarteSur(&(LigneR7[Co]));
    }
}

/* Visualisation des �tats du jeu */

void AfficherR7()
{
  Couleur Co;

  EffacerGraphique();
  AfficherTas(TalonR7, "Talon");
  AfficherTas(RebutR7, "Rebut");

  for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++)
    AfficherTas(LigneR7[Co], TexteCouleurR7[Co]);

/* AttendreCliquer() */
  usleep(500 000);
}

/* Jouer le relais des 7 */

void JouerTasR7(Tas *T, booleen *OK)
{
  Couleur Co;
  Rang RT, RSous, RSur;

  Co = LaCouleur(CarteSur(*T));
  RT = LeRang(CarteSur(*T));
  RSous = LeRang(CarteSous(LigneR7[Co]));
  RSur = LeRang(CarteSur(LigneR7[Co]));

  *OK = vrai;
  if (RT == RangSuivant(RSur))
    DeplacerHautSur(T, &(LigneR7[Co]));
  else if (RSous == RangSuivant(RT))
    DeplacerHautSous(T, &(LigneR7[Co]));
  else
    *OK = faux;
}

void JouerUnTourR7(ModeTrace MT)
{
  booleen OK;

  if (MT == AvecTrace)
    AfficherR7();
  do	/* Jeu du talon, puis �ventuellement du rebut */ {
      /* On sait qu'on ne peut pas jouer le rebut et que le talon n'est pas vide */
      /* Jouer le talon */
      RetournerCarteSur(&TalonR7);
      JouerTasR7(&TalonR7, &OK);
      if (!OK)
	      DeplacerHautSur(&TalonR7, &RebutR7);
      if (MT == AvecTrace)
	      AfficherR7();
      while (OK && !TasVide(RebutR7))	{
	      /* On a jou� le talon ou le rebut. Le rebut n'est pas vide: on joue le rebut */
	      JouerTasR7(&RebutR7, &OK);
	      if (OK && (MT == AvecTrace))
	         AfficherR7();
	   }
  } while (!TasVide(TalonR7));
}

int JouerUneR7(int NMaxT, ModeTrace MT)
{
  printf("JouerUneR7.enter\n");
  JouerUnTourR7(MT);
  printf("JouerUneR7 fin de jouer un tour\n");
  /* Jeu d'au plus NMaxT tours */

  while (!(TasVide(RebutR7)) && (NumTourR7 < NMaxT))
    {
      RetournerTas(&RebutR7);
      PoserTasSurTas(&RebutR7, &TalonR7);
      JouerUnTourR7(MT);
      NumTourR7 = NumTourR7 + 1;
    }
  if (TasVide(RebutR7)) {
      printf("Vous avez gagne en %d tours !\n",NumTourR7);
      return NumTourR7;
  }
  else {
     printf("Vous avez Perdu !\n");
     return 0; /*convention:si perdu, c=0*/
    }
}

void ObserverR7(int NP, int NMaxT)
{
  int i;

  CreerTableauInitialR7();
  JouerUneR7(NMaxT, AvecTrace);
  for (i = 1; i <= NP-1; i++)
    {
      ReformerTableauInitialR7();
      JouerUneR7(NMaxT, AvecTrace);
    }
}

void AnalyserR7(int NP, int NMaxT) /*procedure qui stocke les resultats dans un tableau et permet de faire les statistiques*/
{
   int i;
   int resultat;
   int stats[NMaxT+1];
   int k;
   for (k=0;k < NMaxT+1;k++){
     stats[k]=0;
   }
  CreerTableauInitialR7();
  resultat=JouerUneR7(NMaxT, SansTrace);
  stats[resultat]+=1;
  for (i = 1; i <= NP-1; i++)
  {
      ReformerTableauInitialR7();
      resultat=JouerUneR7(NMaxT, SansTrace);
      stats[resultat]+=1;
  }
  printf("\nStatistiques de ce jeu de Reussite sur %d parties, chacune avec %d tours au maximum:\n", NP, NMaxT);
  printf("vous avez perdu %d %% des fois\n",100*stats[0]/NP);
  i=1;
  int counter=stats[0];
  while (i<NMaxT && counter<NP) {
    counter+=stats[i];
    printf("vous avez gagne %d %% des fois apres %d tours \n",100*stats[i]/NP,i);
    i++;
  }
  printf("\nStatistiques avanc�es:\n");
  i=1;
  counter=stats[0];
  while (i<NMaxT && counter<NP) {
    counter+=stats[i];
    printf("votre probabilite de gagner est %d %% apres %d tours \n",100*counter/NP,i);
    i++;
  }
}
