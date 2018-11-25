/*--------------------------------------------------------------*/
/* Reussites. Michel Bonin, Catherine Parent, octobre 2005,
d'apres les algorithmes de Pierre-Claude Scholl
modifie par F. Carrier, juillet 2012
--> types enumeres : Couleur, Rang
--> tas representes par des listes chainees
----------------------------------------------------------------*/

#include "Tas.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*-----------------------------------*/
/* Specifications des objets de base */
/*-----------------------------------*/

/* Couleurs et rangs */

/* Couleurs */
/* Ordre croissant sur les couleurs: trefle, carreau, coeur, pique */

Couleur CouleurSuivante(Couleur C)
{
	if(C == DerniereCouleur)
	{
		return PremiereCouleur;
	}
	else
	{
		return C+1;
	}
}

/* Rangs */
/* Ordre croissant sur les rangs: deux, ..., dix, valet, dame, roi, as */

Rang RangSuivant(Rang R)
{
	if(R == DernierRang)
	{
		return Deux;
	}
	else
	{
		return R+1;
	}
}

/*--------------------------------------------------------------------*/
/* Representation des primitives de manipulation des cartes et des tas*/
/*--------------------------------------------------------------------*/

/* Representation des cartes */

/* Testeurs et selecteurs */

Rang LeRang(Carte C)
{
	return C.RC;
}

Couleur LaCouleur(Carte C)
{
	return C.CC;
}

Visibilite EstCachee(Carte C)
{
	return C.VC == Cachee;
}

Visibilite EstDecouverte(Carte C)
{
	return C.VC == Decouverte;
}

/* Comparaison de cartes */

booleen RangInferieur(Carte C1, Carte C2)
{
	return LeRang(C1) < LeRang(C2);
}

booleen MemeRang(Carte C1, Carte C2)
{
	return LeRang(C1) == LeRang(C2);
}

booleen CouleurInferieure(Carte C1, Carte C2)
{
	return LaCouleur(C1) < LaCouleur(C2);
}

booleen MemeCouleur(Carte C1, Carte C2)
{
	return LaCouleur(C1) == LaCouleur(C2);
}

booleen EstCarteAvant(Carte C1, Carte C2)
{
	if (!MemeCouleur(C1,C2))
	{
		return CouleurInferieure(C1,C2);
	}
	else
	{
		return RangInferieur(C1,C2);
	}
}

/* Representation des tas */

/* Testeurs et selecteurs */

booleen TasActif(Tas T)
{
	return (T.RT==actif);
}

booleen TasVide(Tas T)
{
	return (T.HT==0);
}

booleen TasEmpile(Tas T)
{
	return (T.MT==empile);
}

booleen TasEtale(Tas T)
{
	return (T.MT==etale);
}

int LaHauteur(Tas T)
{
	return T.HT;
}

Localisation LaPlace(Tas T)
{
	return T.LT;
}

/* Constructeurs */

/* *************************************************************
void CreerTasVide(Localisation L, Mode M, Tas *T)
associe � T un tas vide actif plac� en L et de mode d'�talement M.
Pr�-condition : l'emplacement L est disponible
**************************************************************** */
void CreerTasVide(Localisation L, Mode M, Tas *T)
{
	(*T).LT = L;
	(*T).RT = actif;
	(*T).MT = M;
	(*T).HT = 0;
	(*T).tete = NULL ;
	(*T).queue = NULL ;
}

/* *************************************************************
void SupprimerTasVide(Tas *T)
rend le tas vide inactif. En particulier, la place qu'il occupait
devient libre pour un autre tas.
Pr�-condition : le tas T est vide et actif
**************************************************************** */
void SupprimerTasVide(Tas *T)    /*en cours-Marco*/
{
	if (T->HT==0)
	{
		T->RT=inactif;
		T->LT.NC=0;
		T->LT.NL=0;
	}
}

/* *************************************************************
void CreerJeuNeuf(int N, Localisation L, Tas *T)
forme en L le tas empil� T avec l'ensemble des N cartes du jeu dans
l'ordre des cartes et faces cach�es.
Donne leur valeur aux variables globales NbCartes et PremierRang.
Pr�-condition : l'emplacement L est libre
N==52 ou N==32
**************************************************************** */
void CreerJeuNeuf(int N, Localisation L, Tas *T){
	Rang PremierRang;
	if (N==52) {
		PremierRang=Deux;
	}
	else if (N==32) {
		PremierRang=Sept;
	}
	struct adCarte *fausseQueue=(struct adCarte*)malloc(sizeof(struct adCarte)); /* creation fictif1 */
	struct adCarte *fausseTete=(struct adCarte*)malloc(sizeof(struct adCarte)); /* creation fictif2 */
	fausseTete->prec=T->tete;
	fausseTete->suiv=fausseQueue;
	fausseQueue->prec=fausseTete;
	fausseQueue->suiv=fausseTete;
	T->tete=fausseTete;
	T->queue=fausseQueue;
	T->HT=0;
	Couleur Co;
	Rang Ra;
	for (Co=Trefle; Co <= Pique;Co++){
		for (Ra=PremierRang;Ra <= As;Ra++) {
			struct adCarte *nouveauElt=(struct adCarte*)malloc(sizeof(struct adCarte));
			nouveauElt->prec=fausseTete;
			nouveauElt->suiv=fausseQueue;
			fausseQueue->prec=nouveauElt;
			fausseTete->suiv=nouveauElt;
			nouveauElt->elt.CC=Co;
			nouveauElt->elt.RC=Ra;
			nouveauElt->elt.VC=Cachee;
			T->HT++;
			fausseTete=nouveauElt;
		}
	}
	fausseTete=T->tete; /* on remet la fausse tete � son emplacement initial pour la liberer */
	T->tete=fausseTete->suiv;
	T->queue=fausseQueue->prec; /* la queue du Tas pointe vers le dernier element */
	T->tete->prec=NULL; T->queue->suiv=NULL; /* pas de creation de liste circulaire */
	free(fausseTete); free(fausseQueue); /* liberation fictifs */
	T->RT=actif;
	T->MT=empile;
	T->LT=L;
}


/* Consultation des cartes d'un tas: ne deplace pas la carte */

/* *************************************************************
Carte CarteSur(Tas T) {
carte situee au dessus du tas
**************************************************************** */
Carte CarteSur(Tas T)
{
  if(T.HT > 0)
  {
	return T.queue->elt;
  }
}
/* *************************************************************
Carte CarteSous(Tas T) {
carte situee au dessous du tas
**************************************************************** */
Carte CarteSous(Tas T)
{
  if(T.HT > 0)
  {
	return T.tete->elt;
  }
}
/* *************************************************************
Carte IemeCarte(Tas T, int i)
ieme carte dans T (de bas en haut).
Pr�condition : i <= LaHauteur(T)
**************************************************************** */
Carte IemeCarte(Tas T, int i)
{
	struct adCarte *Visitor;
	Visitor = T.tete ;
	int k = 1;
	while (k < i && Visitor->suiv != NULL)   /*Marco:while pour protection en cas de problèmes de initialisation du tas*/
	{
		Visitor = Visitor->suiv;
		k++;
	}
	return Visitor->elt;
}

/* Retournement d'une carte sur un tas */

/* *************************************************************
void RetournerCarteSur(Tas *T)
retourne la carte situ�e au dessus du tas T.
Pr�-condition : T non vide
**************************************************************** */
void RetournerCarteSur(Tas *T)
{
	if (T->HT > 0)
	{
		if (!(*T).queue->elt.VC)
		{
			(*T).queue->elt.VC = Decouverte;
		}
		else
		{
			(*T).queue->elt.VC = Cachee;
		}
	}
}

/* *************************************************************
void RetournerCarteSous(Tas *T)
retourne la carte situ�e au dessous du tas T.
Pr�-condition : T non vide
**************************************************************** */
void RetournerCarteSous(Tas *T)
{
	if (!(*T).tete->elt.VC)
	{
		(*T).tete->elt.VC = Decouverte;
	}
	else
	{
		(*T).tete->elt.VC = Cachee;
	}
}

/* Modification d'un tas */

/* *************************************************************
void EmpilerTas(Tas *T)
void EtalerTas(Tas *T)
modification du mode d'etalement d'un tas
**************************************************************** */
void EmpilerTas(Tas *T)
{
	(*T).MT = empile;

}

void EtalerTas(Tas *T)
{
	(*T).MT = etale;
}


/* *************************************************************
void EchangerCartes(int i, int j, Tas *T)
echange les cartes i et j du tas T
Precondition : les deux cartes existent i,j <= LaHauteur(T)
**************************************************************** */
void EchangerCartes(int i, int j, Tas *T)
{
	/*struct adCarte *carteI = IemeCarte(*T,i);
	struct adCarte *carteJ = IemeCarte(*T,j);
	struct adCarte *tempI = carteI;
	struct adCarte *tempJ = carteJ;*/
	Carte carteI = IemeCarte(*T,i);
	Carte carteJ = IemeCarte(*T,j);
	struct adCarte *Visitor;
	Visitor = T->tete ;
	int k = 1;
	while (k < j && Visitor->suiv != NULL)   /*Marco:while pour protection en cas de problèmes de initialisation du tas*/
	{
		Visitor = Visitor->suiv;
		k++;
	}
	Visitor->elt=carteI;
	Visitor = T->tete ;
	k = 1;
	while (k < i && Visitor->suiv != NULL)   /*Marco:while pour protection en cas de problèmes de initialisation du tas*/
	{
		Visitor = Visitor->suiv;
		k++;
	}
	Visitor->elt=carteJ;
}

/* *************************************************************
void BattreTas(Tas *T)
bas le tas T
**************************************************************** */

void BattreTas(Tas *T)
{
	int i = 51;
	int j = 51;
	int nbfois = 0;
	int e; int f;
	srand(time(NULL));

	while (nbfois < 5000)
	{
		e = rand()%i + 1;
		f = rand()%j + 1;
		EchangerCartes( e, f, T );
		nbfois++;
	}
}


/* ******************************************************************************
void RetournerTas(Tas *T)
retourne le tas T : la premiere devient la derniere et la visibilite est inversee
********************************************************************************* */
void RetournerTas(Tas *T)
{
	struct adCarte* sauveTete = T->tete->suiv ;
	struct adCarte* sauveQueue = T->queue ;
	T->tete->elt.VC = (T->tete->elt.VC == Decouverte) ? Cachee : Decouverte;
	T->tete->suiv = NULL ;
	T->tete->prec = T->queue;
	T->queue->suiv = T->tete;
	sauveTete->prec = NULL ;
	T->tete = sauveTete ;
	sauveQueue = sauveQueue->suiv;

	while(T->queue->prec != NULL)
	{
		sauveTete = T->tete->suiv ;
		sauveTete->elt.VC = (sauveTete->elt.VC == Decouverte) ? Cachee : Decouverte;
		sauveTete->prec = NULL;
		T->tete->prec = T->queue;
		T->tete->suiv = T->queue->suiv;
		T->queue->suiv = T->tete;
		T->tete->suiv->prec = T->tete;
		T->tete = sauveTete;
	}
	T->queue = sauveQueue;
}


/* Deplacements de cartes d'un tas sur un autre */


/* ******************************************************************************
void AjouterCarteSurTas (adCarte *ac, Tas *T)
ajoute la carte d'adresse ac sur le tas T
********************************************************************************* */
void AjouterCarteSurTas (struct adCarte *ac, Tas *T)    /*surTas = queue*/
{
	if (T->HT == 0) {
		T->tete = ac;
		T->queue = ac;
		T->queue->suiv=NULL;
		T->tete->prec=NULL;
		T->HT++; /*augmentation taille tas*/
	}
	else {
		ac->suiv = NULL;
		ac->prec = T->queue;
		T->queue->suiv=ac;
		T->queue = ac;
		T->HT++; /*augmentation taille tas*/
	}
}

/* ******************************************************************************
void AjouterCarteSousTas (adCarte *ac, Tas *T)
ajoute la carte d'adresse ac sous le tas T
********************************************************************************* */
void AjouterCarteSousTas (struct adCarte *ac, Tas *T)   /*sousTas = tete*/
{
	if (T->HT == 0) {
		T->tete = ac;
		T->queue = ac;
		T->tete->suiv=NULL;
		T->tete->prec=NULL;
		T->HT++; /*augmentation taille tas*/
	}
	else {
		ac->suiv = T->tete;
		ac->prec = NULL;
		T->tete->prec=ac;
		T->tete = ac;
		T->HT++; /*augmentation taille tas*/
	}
}


/* ******************************************************************************
void DeplacerHautSur(Tas *T1, Tas *T2)
enl�ve la carte situ�e au dessus de T1 et la place au dessus de T2
Pr�-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerHautSur(Tas *T1, Tas *T2)
{
	if (T1->tete != NULL && T2->RT == actif)
	{
		struct adCarte *temporaire=T1->queue->prec;
		AjouterCarteSurTas(T1->queue, T2);
		T1->queue=temporaire;
		if(T1->HT>1){
			temporaire->suiv=NULL;
			T1->HT-=1;
		}
		else {
			T1->HT=0;
		}
	}
}

/* ******************************************************************************
void DeplacerHautSous(Tas *T1, Tas *T2)
enl�ve la carte situ�e au dessus de T1 et la place au dessous de T2.
Pr�-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerHautSous(Tas *T1, Tas *T2)
{
	if (T1->tete != NULL && T2->RT == actif)
	{
		struct adCarte *temporaire=T1->queue->prec;
		AjouterCarteSousTas(T1->queue, T2);
		T1->queue=temporaire;
		if(T1->HT>1){
			T1->queue->suiv=NULL;
			T1->HT-=1; /*diminution taille tas*/
		}
		else {
			T1->HT=0;
		}
	}
}

/* ******************************************************************************
void DeplacerBasSur(Tas *T1, Tas *T2)
enl�ve la carte situ�e au dessous de T1 et la place au dessus de T2.
Pr�-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerBasSur(Tas *T1, Tas *T2)
{
	if (T1->tete != NULL && T2->RT == actif)
	{
		struct adCarte *temporaire=T1->tete->suiv;
		AjouterCarteSurTas(T1->tete, T2);
		T1->tete=temporaire;
		if(T1->HT>1){
			T1->tete->prec=NULL;
			T1->HT-=1;
		}
		else {
			T1->HT=0;
		}
	}
}

/* ******************************************************************************
void DeplacerBasSous(Tas *T1, Tas *T2) {
enl�ve la carte situ�e au dessous de T1 et la place au dessous de T2.
Pr�-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerBasSous(Tas *T1, Tas *T2)
{
	if (T1->tete != NULL && T2->RT == actif)
	{
		struct adCarte *temporaire=T1->tete->suiv;
		AjouterCarteSousTas(T1->tete, T2);
		T1->tete=temporaire;
		if(T1->HT>1){
			T1->tete->prec=NULL;
			T1->HT-=1;
		}
		else {
			T1->HT=0;
		}
	}
}

/* ******************************************************************************
void DeplacerCarteSur(Couleur C, Rang R, Tas *T1, Tas *T2)
enl�ve du tas T1, la carte de couleur C et de rang R et la place au dessus de T2.
Pr�-condition : T1 contient la carte et T2 est actif.
********************************************************************************* */
void DeplacerCarteSur(Couleur C, Rang R, Tas *T1, Tas *T2)
{
	struct adCarte *visiteur = T1->tete;
	int trouve=0 ;
	while(visiteur != NULL && (visiteur->elt.RC != R) && (visiteur->elt.CC != C))
	{
		visiteur = visiteur->suiv;
	}
	if (visiteur == NULL)
		 {
		 trouve = 0;
	   }
	else
		 {
	   trouve = 1
     }

	if(T2->RT == actif && trouve == 1)
	{
		visiteur = T1->tete;
		while(visiteur != NULL && (visiteur->elt.RC != R) && (visiteur->elt.CC != C))
		{
			visiteur = visiteur->suiv;
		}
		if(visiteur == NULL || visiteur->elt.RC != R || visiteur->elt.CC != C)
		{
			exit(0);
		}
		else
		{
			visiteur->prec->suiv = visiteur->suiv;
			visiteur->suiv->prec = visiteur->prec;
			visiteur->prec = NULL;
			visiteur->suiv = NULL;
			AjouterCarteSurTas(visiteur, T2);
			T1->HT -= 1;
		}
	}
}



/* ******************************************************************************
void PoserTasSurTas(Tas *T1, Tas *T2)
pose le tas T1 sur le tas T2.
Les deux tas doivent avoir le m�me mode d'�talement.
A l'�tat final, le tas T1 est vide mais toujours actif, et le tas T2 comporte (de bas en
haut) toutes les cartes qu'il avait au d�part puis toutes les cartes de T1 dans l'ordre
qu'elles avaient au d�part dans chacun des tas.
Cette op�ration ne modifie ni la visibilit� des cartes, ni la localisation des tas T1 et T2,
ni leur mode d'�talement.
********************************************************************************* */
void PoserTasSurTas(Tas *T1, Tas *T2)
{
	if(T1->MT == T2->MT)
	{
		T2->queue->suiv = T1->tete;
		T1->tete->prec=T2->queue;
		T2->queue=T1->queue;
		T1->RT = actif;
		T2->HT+=T1->HT;
		T1->HT=0;
		T1->tete = NULL;
		T1->queue = NULL;

	}
}
