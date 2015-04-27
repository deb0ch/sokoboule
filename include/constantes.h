/*
constantes.h
------------

Par Deb0ch, grâce au site du zer0 !

Rôle: Définition des constantes communes à tout le programme (taille de la fenêtre...)

*/

#ifndef CONSTANTES_H
#define CONSTANTES_H

#define TAILLE_BLOC         32 //En pixels
#define NB_BLOCS_LARGEUR    25
#define NB_BLOCS_HAUTEUR    15
#define TAILLE_NIVEAU       (6 + 2 * 3 * NB_BLOCS_HAUTEUR * NB_BLOCS_LARGEUR + 1)
#define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR
#define HAUTEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_HAUTEUR
#define NOM_FICHIER "levels/niveaux.lvl"

enum {HAUT, BAS, GAUCHE, DROITE};

typedef			struct CASE_MAP
{
  enum
    {
      VIDE,
      MUR,
      CAISSE,
      OBJECTIF,
      INUK,
      CAISSE_OK
    }			type;
  enum
    {
      NONE,
      MUR_BORDH,
      MUR_BORDB,
      MUR_BORDG,
      MUR_BORDD,
      MUR_COINHG,
      MUR_COINHD,
      MUR_COINBG,
      MUR_COINBD,
      MUR_COINHGB,
      MUR_COINHDB,
      MUR_COINBGB,
      MUR_COINBDB,
      MUR_COINHGB2,
      MUR_COINHDB2,
      MUR_BLOC1,
      MUR_CAILLOU_GLACE,
      MUR_CAILLOU_SOL1,
      MUR_CAILLOU_GLACEB,
      SOL_GLACE,
      SOL_GLACE_FISSURE,
      SOL_SOL2,
      SOL_ESCALIER_HAUT,
      SOL_ESCALIER_BAS,
      SOL_ESCALIER_GAUCHE,
      SOL_ESCALIER_DROITE,
      OBJ_TROU_SOL1,
      OBJ_TROU_SOL2,
      CAISSE_BOIS,
      CAISSE_BOISOK,
      INUK_HAUT,
      INUK_BAS,
      INUK_GAUCHE,
      INUK_DROITE,
      MENU_BRAVO,
      GRAPHISME_LAST
    }			graphisme;
}			CASE_MAP;

#endif
