/*--------------------------------------------------------------*/
/* Reussites. Michel Bonin, Catherine Parent, octobre 2005,
   d'apres les algorithmes de Pierre-Claude Scholl
   modifie par F. Carrier, juillet 2012
   --> types enumeres : Couleur, Rang
   --> tas representes par des listes chainees
----------------------------------------------------------------*/

//#include "Tas.h"
//#include "Alea.h"
#include "TasACompleter.h"

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
    if ((*T).HT==0)
    {
        (*T).RT=inactif;
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
/*void CreerJeuNeuf(int N, Localisation L, Tas *T)
{
    
#define PremierRang 2
#define N 52
    struct adCarte *fictif=(struct adCarte*)malloc(sizeof(struct adCarte));
    fictif->suiv=T->tete;
    struct adCarte *AdPred=fictif;
    struct adCarte *AdSuiv=fictif;
    for (couleur=DerniereCouleur; couleur=PremiereCouleur; couleur--)
    {
        for (rang=DernierRang; rang=PremierRang; rang--)
        {
            struct adCarte *X=(struct adCarte*)malloc(sizeof(struct adCarte));
            AdSuiv=X;
            AdSuiv->prec=AdPred;
            AdPred->suiv=AdSuiv;
            AdSuiv->elt.CC=couleur;
            AdSuiv->elt.RC=rang;
            AdSuiv->elt.VC=cachee;
            AdPred=AdSuiv
        }
        T->tete=fictif->suiv;
        T->queue=AdSuiv;
        T->queue->suiv=NULL;
        free(fictif);
    }
}

*/


/* Consultation des cartes d'un tas: ne deplace pas la carte */

/* *************************************************************
Carte CarteSur(Tas T) {
carte situee au dessus du tas
**************************************************************** */
Carte CarteSur(Tas T)
{
    return T.tete->elt;
}

/* *************************************************************
Carte CarteSous(Tas T) {
carte situee au dessous du tas
**************************************************************** */
Carte CarteSous(Tas T)
{
return T.queue->elt;
}

/* *************************************************************
Carte IemeCarte(Tas T, int i)
ieme carte dans T (de bas en haut).
Pr�condition : i <= LaHauteur(T)
**************************************************************** */
Carte IemeCarte(Tas T, int i)
{
    while (i <= LaHauteur(T))
    {
        {
            struct adCarte *Visitor;
            Visitor = T.tete ;
            int k = 0;
            while (k < i && Visitor->elt! = NULL)   /*Marco:while pour protection en cas de problèmes de initialisation du tas*/
            {
                Visitor = Visitor->suiv;
            }
            return Visitor->elt;
        }
    }
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
    struct adCarte *carteI = IemeCarte(*T,i);
    struct adCarte *carteJ = IemeCarte(*T,j);
    struct adCarte *tempI = carteI;
    struct adCarte *tempJ = carteJ;
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

    srand(time(NULL));

    while (nbfois < 500)
    {
        rand()%i + 0;
        rand()%j + 0;
        EchangerCartes( i, j, *T );
        nbfois++;
    }
}



/* ******************************************************************************
void RetournerTas(Tas *T)
retourne le tas T : la premiere devient la derniere et la visibilite est inversee
********************************************************************************* */
void RetournerTas(Tas *T)
{
    /*inverser queue et tete*/
    struct adCarte temp = T->tete ;
    T->tete = T->queue;
    T->queue = temp;

    /*changer la visibilité*/
    struct adCarte visitor = T->tete ;
    while(visitor != T->queue)
    {
        if (visitor->elt.VC = Decouverte)
        {
            visitor->elt.VC = Cachee;
        }
        else
        {
            visitor->elt.VC = Decouverte;
        }
        visitor = visitor->suiv;
    }
}

/* Deplacements de cartes d'un tas sur un autre */


/* ******************************************************************************
void AjouterCarteSurTas (adCarte *ac, Tas *T)
ajoute la carte d'adresse ac sur le tas T
********************************************************************************* */
void AjouterCarteSurTas (struct adCarte *ac, Tas *T)    /*surTas = queue*/
{
    ac->suiv = NULL;
    ac->prec = T->queue;
    T->queue = ac;
}

/* ******************************************************************************
void AjouterCarteSousTas (adCarte *ac, Tas *T)
ajoute la carte d'adresse ac sous le tas T
********************************************************************************* */
void AjouterCarteSousTas (struct adCarte *ac, Tas *T)   /*sousTas = tete*/
{
    ac->suiv = T->tete;
    ac->prec = NULL;
    T->tete = ac;
}

/* ******************************************************************************
void DeplacerHautSur(Tas *T1, Tas *T2)
enl�ve la carte situ�e au dessus de T1 et la place au dessus de T2
Pr�-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerHautSur(Tas *T1, Tas *T2)
{
    if (T1->tete != NULL && T2.RT == actif)
    {
        AjouterCarteSurTas(T1->queue, *T2)
    }
}

/* ******************************************************************************
void DeplacerHautSous(Tas *T1, Tas *T2)
enl�ve la carte situ�e au dessus de T1 et la place au dessous de T2.
Pr�-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerHautSous(Tas *T1, Tas *T2)
{
    if (T1->tete != NULL && T2.RT == actif)
    {
        AjouterCarteSousTas(T1->queue, *T2)
    }
}

/* ******************************************************************************
void DeplacerBasSur(Tas *T1, Tas *T2)
enl�ve la carte situ�e au dessous de T1 et la place au dessus de T2.
Pr�-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerBasSur(Tas *T1, Tas *T2)
{
    if (T1->tete != NULL && T2.RT == actif)
    {
        AjouterCarteSurTas(T1->tete, *T2)
    }
}

/* ******************************************************************************
void DeplacerBasSous(Tas *T1, Tas *T2) {
enl�ve la carte situ�e au dessous de T1 et la place au dessous de T2.
Pr�-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerBasSous(Tas *T1, Tas *T2)
{
    if (T1->tete != NULL && T2.RT == actif)
    {
        AjouterCarteSousTas(T1->tete, *T2)
    }
}

/* ******************************************************************************
void DeplacerCarteSur(Couleur C, Rang R, Tas *T1, Tas *T2)
enl�ve du tas T1, la carte de couleur C et de rang R et la place au dessus de T2.
Pr�-condition : T1 contient la carte et T2 est actif.
********************************************************************************* */
void DeplacerCarteSur(Couleur C, Rang R, Tas *T1, Tas *T2)
{
    if(T2->RT == actif)
    {
        struct adCarte *visiteur = T1->tete;
        while(*visiteur != NULL && (visiteur->elt.CC != R & visiteur->elt.RC != C))
        {
            *visiteur = visiteur->suiv;
        }
        if(*visiteur = NULL)
        {
            printf("La carte demandée de rang %d et de couleur %d n'est pas dans le tas !", R, C);
        }
        else /*Carte trouvée, on l'a déplace au dessus de T2*/
        {
            (visiteur->prec)->suiv = visiteur->suiv;
            (visiteur->suiv)->prec = visiteur->prec;
            AjouterCarteSurTas(visiteur, *T2);
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
        T1->RT = actif;
        T1->HT = 0;
        T1->tete = NULL;
        T1->queue = NULL;
    }
}
