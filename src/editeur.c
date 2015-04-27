/*
  editeur.h
  ----------

  Par Deb0ch, grâce au site du zer0 !

  Rôle: Editeur de niveaux

*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constantes.h"
#include "jeu.h"
#include "editeur.h"
#include "fichiers.h"




void editeur(SDL_Surface* ecran){

  SDL_Surface **images , *cursor = NULL;
  SDL_Rect posInuk , posCursor = {0} , coordActuelles;
  SDL_Event event;

  int continuer = 1 , niveauActuel = 1 , clicGaucheEnCours = 0 , clicDroitEnCours = 0 , i , j;
  CASE_MAP carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0} , objetActuel;

  objetActuel.type = MUR;
  objetActuel.graphisme = MUR_BLOC1;

  chargerImages(&images);

  if(!chargerCarte(carte , &niveauActuel)){
#ifdef WIN32
    MessageBox(0 , "Impossible de charger le niveau" , "ERREUR" , MB_ICONEXCLAMATION);
#else
    printf("Impossible de charger le niveau\n");
#endif
    fprintf(stderr , "Impossible de charger le niveau");
    return ;
  }

  posInuk.x = -1;
  posInuk.y = -1;

  detecterJoueur(carte , &posInuk);

  cursor = images[MUR_BLOC1];

  while(continuer){

    SDL_WaitEvent(&event);
    switch(event.type){

    case SDL_MOUSEBUTTONDOWN:

      posCursor.x = event.button.x;
      posCursor.y = event.button.y;

      if (event.button.button == SDL_BUTTON_LEFT){

	coordActuelles.x = event.button.x / TAILLE_BLOC;
	coordActuelles.y = event.button.y / TAILLE_BLOC;
	poserObjet(&carte[event.button.x / TAILLE_BLOC][event.button.y /TAILLE_BLOC] , coordActuelles , objetActuel , &posInuk);

	clicGaucheEnCours = 1;
      }
      else if (event.button.button == SDL_BUTTON_RIGHT) {

	carte[event.button.x / TAILLE_BLOC][event.button.y /TAILLE_BLOC].type = VIDE;
	carte[event.button.x / TAILLE_BLOC][event.button.y /TAILLE_BLOC].graphisme = NONE;

	if(event.button.x / TAILLE_BLOC == posInuk.x && event.button.y /TAILLE_BLOC == posInuk.y){
	  posInuk.x = -1;
	  posInuk.y = -1;
	}
	clicDroitEnCours = 1;
      }

      break;

    case SDL_MOUSEBUTTONUP:
      if (event.button.button == SDL_BUTTON_LEFT)
	clicGaucheEnCours = 0;
      else if (event.button.button == SDL_BUTTON_RIGHT)
	clicDroitEnCours = 0;
      break;

    case SDL_MOUSEMOTION:

      posCursor.x = event.motion.x;
      posCursor.y = event.motion.y;

      if (clicGaucheEnCours){

	coordActuelles.x = event.button.x / TAILLE_BLOC;
	coordActuelles.y = event.button.y / TAILLE_BLOC;
	poserObjet(&carte[event.button.x / TAILLE_BLOC][event.button.y /TAILLE_BLOC] , coordActuelles , objetActuel , &posInuk);
      }
      else if (clicDroitEnCours){

	carte[event.button.x / TAILLE_BLOC][event.button.y /TAILLE_BLOC].type = VIDE;
	carte[event.button.x / TAILLE_BLOC][event.button.y /TAILLE_BLOC].graphisme = NONE;

	if(event.button.x / TAILLE_BLOC == posInuk.x && event.button.y / TAILLE_BLOC == posInuk.y){
	  posInuk.x = -1;
	  posInuk.y = -1;
	}
      }
      break;

    case SDL_KEYDOWN:
      switch(event.key.keysym.sym){

      case SDLK_ESCAPE:
	continuer = 0;
	break;

      case SDLK_s:
	sauverCarte(carte , posInuk , niveauActuel);
	break;

      case SDLK_c:
	chargerCarte(carte , &niveauActuel);
	detecterJoueur(carte , &posInuk);
	break;

      case SDLK_n:
	creerCarte(carte , &niveauActuel);
	chargerCarte(carte , &niveauActuel);
	detecterJoueur(carte , &posInuk);
	break;

      case SDLK_RIGHT :

	++niveauActuel;

	chargerCarte(carte , &niveauActuel);
	detecterJoueur(carte , &posInuk);
	break;

      case SDLK_LEFT :

	if(niveauActuel > 1)
	  --niveauActuel;

	chargerCarte(carte , &niveauActuel);
	detecterJoueur(carte , &posInuk);
	break;

      case SDLK_q:
	objetActuel.type = VIDE;
	objetActuel.graphisme = SOL_ESCALIER_BAS;
	break;

      case SDLK_w:
	objetActuel.type = VIDE;
	objetActuel.graphisme = SOL_ESCALIER_GAUCHE;
	break;

      case SDLK_e:
	objetActuel.type = VIDE;
	objetActuel.graphisme = SOL_ESCALIER_DROITE;
	break;

      case SDLK_r:
	objetActuel.type = VIDE;
	objetActuel.graphisme = SOL_ESCALIER_HAUT;
	break;

      case SDLK_KP0:
	objetActuel.type = VIDE;
	objetActuel.graphisme = SOL_SOL2;
	break;

      case SDLK_KP1:
	objetActuel.type = MUR;
	objetActuel.graphisme = MUR_COINBG;
	break;

      case SDLK_KP2:
	objetActuel.type = MUR;
	objetActuel.graphisme = MUR_BORDB;
	break;

      case SDLK_KP3:
	objetActuel.type = MUR;
	objetActuel.graphisme = MUR_COINBD;
	break;

      case SDLK_KP4:
	objetActuel.type = MUR;
	objetActuel.graphisme = MUR_BORDG;
	break;

      case SDLK_KP5:
	objetActuel.type = VIDE;
	objetActuel.graphisme = SOL_GLACE;
	break;

      case SDLK_KP6:
	objetActuel.type = MUR;
	objetActuel.graphisme = MUR_BORDD;
	break;

      case SDLK_KP7:
	objetActuel.type = MUR;
	objetActuel.graphisme = MUR_COINHG;
	break;

      case SDLK_KP8:
	objetActuel.type = MUR;
	objetActuel.graphisme = MUR_BORDH;
	break;

      case SDLK_KP9:
	objetActuel.type = MUR;
	objetActuel.graphisme = MUR_COINHD;
	break;

      case SDLK_KP_PLUS:
	objetActuel.type = MUR;
	objetActuel.graphisme = MUR_COINBGB;
	break;

      case SDLK_KP_MINUS:
	objetActuel.type = MUR;
	objetActuel.graphisme = MUR_COINBDB;
	break;

      case SDLK_KP_DIVIDE:
	objetActuel.type = MUR;
	objetActuel.graphisme = MUR_COINHGB;
	break;

      case SDLK_KP_MULTIPLY:
	objetActuel.type = MUR;
	objetActuel.graphisme = MUR_COINHDB;
	break;

      case SDLK_NUMLOCK:
	objetActuel.type = MUR;
	objetActuel.graphisme = MUR_COINHDB2;
	break;

      case SDLK_DELETE:
	objetActuel.type = MUR;
	objetActuel.graphisme = MUR_COINHGB2;
	break;

      case SDLK_1:
	objetActuel.type = CAISSE;
	objetActuel.graphisme = CAISSE_BOIS;
	break;

      case SDLK_2:
	objetActuel.type = CAISSE_OK;
	objetActuel.graphisme = CAISSE_BOISOK;
	break;

      case SDLK_3:
	objetActuel.type = OBJECTIF;
	objetActuel.graphisme = OBJ_TROU_SOL1;
	break;

      case SDLK_4:
	objetActuel.type = INUK;
	objetActuel.graphisme = INUK_BAS;
	break;

      case SDLK_5:
	objetActuel.type = MUR;
	objetActuel.graphisme = MUR_BLOC1;
	break;

      case SDLK_6:
	objetActuel.type = MUR;
	objetActuel.graphisme = MUR_CAILLOU_GLACE;
	break;

      case SDLK_7:
	objetActuel.type = MUR;
	objetActuel.graphisme = MUR_CAILLOU_SOL1;
	break;

      case SDLK_8:
	objetActuel.type = MUR;
	objetActuel.graphisme = MUR_CAILLOU_GLACEB;
	break;

      case SDLK_9:
	objetActuel.type = VIDE;
	objetActuel.graphisme = SOL_GLACE_FISSURE;
	break;

      }
      break;

    case SDL_QUIT : exit(EXIT_SUCCESS);
      break;
    }
    rafraichirCarte(carte , &images , ecran , &posInuk , images[INUK_BAS]);
    cursor = images[objetActuel.graphisme];
    SDL_BlitSurface(cursor , NULL , ecran , &posCursor);
    SDL_Flip(ecran);
  }
  release(&images);
  //SDL_ShowCursor(SDL_ENABLE);
}

void poserObjet(CASE_MAP* caseActuelle , SDL_Rect coordActuelles , CASE_MAP objetActuel , SDL_Rect* posInuk){

  int inukPresent = 0;

  if(coordActuelles.x == posInuk->x && coordActuelles.y == posInuk->y)
    inukPresent = 1;

  switch(objetActuel.type){

  case MUR :
    if(!inukPresent){
      caseActuelle->type = objetActuel.type;
      caseActuelle->graphisme = objetActuel.graphisme;
    }
    break;

  case VIDE :
    if(caseActuelle->type == CAISSE || caseActuelle->type == CAISSE_OK || caseActuelle->type == OBJECTIF){
      caseActuelle->graphisme = objetActuel.graphisme;
    }
    else{
      caseActuelle->type = objetActuel.type;
      caseActuelle->graphisme = objetActuel.graphisme;
    }
    break;

  case CAISSE :
  case CAISSE_OK :
    if(!(caseActuelle->type == MUR || inukPresent == 1)){
      caseActuelle->type = objetActuel.type;
    }
    break;

  case OBJECTIF :
    if(!(caseActuelle->type == MUR)){
      caseActuelle->type = objetActuel.type;
    }
    break;

  case INUK :
    if(caseActuelle->type == VIDE || caseActuelle->type == OBJECTIF){
      posInuk->x = coordActuelles.x;
      posInuk->y = coordActuelles.y;
    }
    break;
  }
}
