/*
main.c
------

Par Deb0ch, grâce au site du zer0 !

Rôle: Fonction principale, initialisation des modules et menu principal

Snowkobowl !

*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constantes.h"
#include "jeu.h"
#include "editeur.h"
#include "fichiers.h"

int main(int argc, char **argv)
{
  SDL_Surface *ecran = NULL, *menu = NULL;
  SDL_Rect positionMenu;
  SDL_Event event;

  int continuer = 1;

  SDL_Init(SDL_INIT_VIDEO);

  SDL_WM_SetIcon(IMG_Load("sprites/caisse_gel.png") , NULL);
  ecran = SDL_SetVideoMode(LARGEUR_FENETRE , HAUTEUR_FENETRE , 32 , SDL_HWSURFACE | SDL_DOUBLEBUF);
  SDL_WM_SetCaption("Sokoboule !" , NULL);

  menu = IMG_Load("sprites/menu_principal.bmp");
  positionMenu.x = 0;
  positionMenu.y = 0;

  while(continuer)
    {
      SDL_WaitEvent(&event);
      switch(event.type)
	{
	case SDL_KEYDOWN :
	  switch(event.key.keysym.sym)
	    {
	    case SDLK_ESCAPE : continuer = 0;
	      break;

	    case SDLK_KP1 :
	    case SDLK_1 : jeu(ecran);
	      break;

	    case SDLK_KP2 :
	    case SDLK_2 : editeur(ecran);
	      break;
	    }
	  break;

	case SDL_QUIT : exit(EXIT_SUCCESS);
	  break;
	}
      SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
      SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
      SDL_Flip(ecran);
    }

  SDL_FreeSurface(ecran);
  SDL_Quit();
  return EXIT_SUCCESS;
}
