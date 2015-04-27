/*
jeu.c
------

Par Deb0ch, grâce au site du zer0 !

Rôle: Le codage du jeu en lui même, fonctions relatives au jeu et à l'affichage de l'écran.

*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constantes.h"
#include "jeu.h"
#include "editeur.h"
#include "fichiers.h"




void jeu(SDL_Surface* ecran){ // La fonction pour jouer.

    SDL_Surface** images;
    SDL_Surface *inukActuel = NULL , *bravo = NULL;
    SDL_Rect positionJoueur , posBravo;
    SDL_Event event;

    int continuer = 1 , niveauActuel = 1 , i = 0 , j = 0; // Continuer vaut 1 tant que le jeu est en cours. Si cette valeur est modifiée, le jeu s'arrête. Chaque valeur autre que 1 nous renseigne sur la cause de l'arrêt de la boucle de jeu: 0 si le joueur quitte volontairement.
    CASE_MAP carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

    chargerImages(&images);

    inukActuel = images[INUK_BAS];

    if(!chargerCarte(carte , &niveauActuel)){
#ifdef WIN32
        MessageBox(0, "Impossible de charger le niveau", "ERREUR", MB_ICONEXCLAMATION);
#else
	printf("ERREUR: Impossible de charger le niveau\n");
#endif

        fprintf(stderr, "Impossible de charger le niveau\n");
        return ;
    }

    if(!detecterJoueur(carte , &positionJoueur)){ // On trouve le joueur sur la carte, on met le type de la case en question à VIDE et on stocke les coordonnées du joueur.
#ifdef WIN32
        MessageBox(0, "Joueur absent du niveau", "ERREUR", MB_ICONEXCLAMATION);
#else
	printf("ERREUR: Joueur absent du niveau\n");
#endif

        fprintf(stderr, "Joueur absent du niveau\n");
        return ;
    }

    SDL_EnableKeyRepeat(100, 100);

    do { // Boucle principale

        while(continuer == 1){
            SDL_WaitEvent(&event);
            switch(event.type){

                        case SDL_KEYDOWN :
                        switch(event.key.keysym.sym){

                        case SDLK_UP :
                            inukActuel = images[INUK_HAUT];
                            deplacerJoueur(carte , &positionJoueur , HAUT); // Fct pour déplacer le joueur avec gestion de collisions.
                        break;

                        case SDLK_DOWN :
                            inukActuel = images[INUK_BAS];
                            deplacerJoueur(carte , &positionJoueur , BAS);
                        break;

                        case SDLK_LEFT :
                            inukActuel = images[INUK_GAUCHE];
                            deplacerJoueur(carte , &positionJoueur , GAUCHE);
                        break;

                        case SDLK_RIGHT :
                            inukActuel = images[INUK_DROITE];
                            deplacerJoueur(carte , &positionJoueur , DROITE);
                        break;

                        case SDLK_r : // On recharge le niveau (Je n'ai pas encore créé un log des mouvements qui permettrait de revenir en arrière d'un ou plusieurs mouvements).
                            chargerCarte(carte , &niveauActuel);
                            if(!detecterJoueur(carte , &positionJoueur)){ // On trouve le joueur sur la carte, on met le type de la case en question à VIDE et on stocke les coordonnées du joueur.
#ifdef WIN32
                                MessageBox(0 , "Joueur absent du niveau" , "ERREUR" , MB_ICONEXCLAMATION);
#else
                                printf("ERREUR: Joueur absent du niveau\n");
#endif

                            fprintf(stderr , "Joueur absent du niveau\n");
                            continuer = 0;
                            }

                        break;

                        case SDLK_KP_PLUS :

                            ++niveauActuel; // On charge le niveau suivant.

                            chargerCarte(carte , &niveauActuel);
                            if(!detecterJoueur(carte , &positionJoueur)){ // On trouve le joueur sur la carte, on met le type de la case en question à VIDE et on stocke les coordonnées du joueur.
#ifdef WIN32
                                MessageBox(0 , "Joueur absent du niveau" , "ERREUR" , MB_ICONEXCLAMATION);
#else
                                printf("ERREUR: Joueur absent du niveau\n");
#endif

                            fprintf(stderr , "Joueur absent du niveau\n");
                            continuer = 0;
                            }
                        break;

                        case SDLK_KP_MINUS :

                            if(niveauActuel > 1)
                                --niveauActuel; // On charge le niveau précédent.

                            chargerCarte(carte , &niveauActuel);
                            if(!detecterJoueur(carte , &positionJoueur)){ // On trouve le joueur sur la carte, on met le type de la case en question à VIDE et on stocke les coordonnées du joueur.
#ifdef WIN32
                                MessageBox(0 , "Joueur absent du niveau" , "ERREUR" , MB_ICONEXCLAMATION);
#else
                                printf("ERREUR: Joueur absent du niveau\n");
#endif

                            fprintf(stderr , "Joueur absent du niveau\n");
                            continuer = 0;
                            }
                        break;

                        case SDLK_ESCAPE : continuer = 0;
                        break;
                    }
                break;

                case SDL_QUIT : exit(EXIT_SUCCESS);
                break;

            }

            if(!rafraichirCarte(carte , &images , ecran , &positionJoueur , inukActuel)) // La fonction refresh l'affichage et renvoie 0 si tous les objectifs sont masqués
                continuer = 2;
            SDL_Flip(ecran);
        }

        if(continuer == 2){

            posBravo.x = LARGEUR_FENETRE/2 - images[MENU_BRAVO]->w/2;
            posBravo.y = HAUTEUR_FENETRE/2 - images[MENU_BRAVO]->h/2;
            SDL_BlitSurface(images[MENU_BRAVO] , NULL , ecran , &posBravo);
            SDL_Flip(ecran); // Affiche le message de fin de niveau.

            do {
                SDL_WaitEvent(&event);
                if(event.type == SDL_QUIT)
                    exit(EXIT_SUCCESS);
            } while(event.key.keysym.sym != SDLK_RETURN && event.key.keysym.sym != SDLK_ESCAPE); // Pause, on attend que le joueur passe.

            ++niveauActuel; // On charge le niveau suivant.

            chargerCarte(carte , &niveauActuel);

            if(!detecterJoueur(carte , &positionJoueur)){ // On trouve le joueur sur la carte, on met le type de la case en question à VIDE et on stocke les coordonnées du joueur.
#ifdef WIN32
                MessageBox(0 , "Joueur absent du niveau" , "ERREUR" , MB_ICONEXCLAMATION);
#else
                printf("ERREUR: Joueur absent du niveau\n");
#endif

                fprintf(stderr , "Joueur absent du niveau\n");
                continuer = 0;
            }

            continuer = 1;

        }

    } while(continuer != 0);

    SDL_EnableKeyRepeat(0, 0);

    release(&images);
}

void deplacerJoueur(CASE_MAP carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction){ // SDL_Rect *pos contient les coordonnées du joueur.

    switch(direction){ // Si il y a un mur ou deux caisses ou le bord de la map devant le joueur on ne fait rien, sinon on déplace le joueur et si il y a une caisse devant lui on la déplace.

        case HAUT :
            if(pos->y - 1 < 0 || carte[pos->x][pos->y - 1].type == MUR)
                break;

            if((carte[pos->x][pos->y - 1].type == CAISSE || carte[pos->x][pos->y - 1].type == CAISSE_OK)
               && (carte[pos->x][pos->y - 2].type == CAISSE || carte[pos->x][pos->y - 2].type == CAISSE_OK || carte[pos->x][pos->y - 2].type == MUR || pos->y - 2 < 0))
               break;

            deplacerCaisse((int*)(&carte[pos->x][pos->y - 1].type), (int*)(&carte[pos->x][pos->y - 2].type));

            pos->y -=1;
        break;

        case BAS :
            if(pos->y + 1 >= NB_BLOCS_HAUTEUR || carte[pos->x][pos->y + 1].type == MUR)
                break;

            if((carte[pos->x][pos->y + 1].type == CAISSE || carte[pos->x][pos->y + 1].type == CAISSE_OK)
               && (carte[pos->x][pos->y + 2].type == CAISSE || carte[pos->x][pos->y + 2].type == CAISSE_OK || carte[pos->x][pos->y + 2].type == MUR || pos->y + 2 >= NB_BLOCS_HAUTEUR))
               break;

            deplacerCaisse((int*)(&carte[pos->x][pos->y + 1].type), (int*)(&carte[pos->x][pos->y + 2].type));

            pos->y +=1;
        break;

        case GAUCHE :
            if(pos->x <= 0 || carte[pos->x - 1][pos->y].type == MUR)
                break;

            if((carte[pos->x - 1][pos->y].type == CAISSE || carte[pos->x - 1][pos->y].type == CAISSE_OK)
               && (carte[pos->x - 2][pos->y].type == CAISSE || carte[pos->x - 2][pos->y].type == CAISSE_OK || carte[pos->x - 2][pos->y].type == MUR || pos->x - 2 < 0))
               break;

            deplacerCaisse((int*)(&carte[pos->x - 1][pos->y].type), (int*)(&carte[pos->x - 2][pos->y].type));

            pos->x -=1;
        break;

        case DROITE :
            if(pos->x + 1 >= NB_BLOCS_LARGEUR || carte[pos->x + 1][pos->y].type == MUR)
                break;

            if((carte[pos->x + 1][pos->y].type == CAISSE || carte[pos->x + 1][pos->y].type == CAISSE_OK)
               && (carte[pos->x + 2][pos->y].type == CAISSE || carte[pos->x + 2][pos->y].type == CAISSE_OK || carte[pos->x + 2][pos->y].type == MUR || pos->y - 2 >= NB_BLOCS_LARGEUR))
               break;

            deplacerCaisse((int*)(&carte[pos->x + 1][pos->y].type), (int*)(&carte[pos->x + 2][pos->y].type));

            pos->x +=1;
        break;
    }
}

void deplacerCaisse(int *case1 , int *case2){ // Prend en paramètre le champ type de deux structures case et déplace une éventuelle caisse de la case1 à la case2

    if(*case1 == CAISSE || *case1 == CAISSE_OK){ // Si une caisse est présente...

        if(*case2 == OBJECTIF) // Si on a un objectif sur la case suivante
            *case2 = CAISSE_OK; // On remplace l'objectif par une caisseOK
        else *case2 = CAISSE; // Sinon on met juste une caisse sur le case suivante

        if(*case1 == CAISSE_OK) // Et si il y avait une caisseOK sur la première case
            *case1 = OBJECTIF; // On révèle l'objectif qui était dessous
        else *case1 = VIDE; // Et sinon, bin il y a plus rien sur la case vuqu'on vient de déplacer la caisse^^
    }
}

int rafraichirCarte(CASE_MAP carte[][NB_BLOCS_HAUTEUR] , SDL_Surface*** images , SDL_Surface* ecran , SDL_Rect* inuk , SDL_Surface* inukActuel){
/* "Blitte" toutes les images correspondant au type et au graphisme de chaque case sur l'écran, et "blitte" le joueur par dessus*/
/* Renvoie 0 si on n'a placé aucun objectif, et 1 si il en reste. Ainsi on sait si on a gagné */
    int i , j , objectifsRestants = 0;
    SDL_Rect position;

    SDL_FillRect(ecran , NULL , SDL_MapRGB(ecran->format , 255 , 255 , 255));

    for(i = 0 ; i < NB_BLOCS_LARGEUR ; ++i){ // On remplit la carte de ses éléments, si on ne place aucun objectif, c'est qu'on a gagné.
        for(j = 0 ; j < NB_BLOCS_HAUTEUR ; ++j){

            position.x = i * TAILLE_BLOC;
            position.y = j * TAILLE_BLOC;

            SDL_BlitSurface((*images)[carte[i][j].graphisme] , NULL , ecran , &position); // On colle d'abord les graphismes de chaque case

            switch(carte[i][j].type){ // Puis on colle les caisses, les objectifs...

                case OBJECTIF :

                    if(carte[i][j].graphisme == SOL_SOL2)
                        SDL_BlitSurface((*images)[OBJ_TROU_SOL2] , NULL , ecran , &position);
                    else SDL_BlitSurface((*images)[OBJ_TROU_SOL1] , NULL , ecran , &position);

                    objectifsRestants = 1;
                break;


                case CAISSE : SDL_BlitSurface((*images)[CAISSE_BOIS] , NULL , ecran , &position);
                break;

                case CAISSE_OK : SDL_BlitSurface((*images)[CAISSE_BOISOK] , NULL , ecran , &position);
                break;
            }
        }
    }

    position.x = inuk->x * TAILLE_BLOC;
    position.y = inuk->y * TAILLE_BLOC;
    SDL_BlitSurface(inukActuel , NULL , ecran , &position); // Et enfin, blittage du joueur à sa position actuelle

    return objectifsRestants;
}

int detecterJoueur(CASE_MAP carte[][NB_BLOCS_HAUTEUR] , SDL_Rect* positionJoueur){

    int i, j, inukPresent = 0;

    for (i = 0 ; i < NB_BLOCS_LARGEUR ; ++i){ // Détection de la position du joueur, stockée dans une structure SDL_Rect, et la case correspondante est mise à VIDE
        for(j = 0 ; j < NB_BLOCS_HAUTEUR ; ++j){

            if(carte[i][j].type == INUK){
                positionJoueur->x = i;
                positionJoueur->y = j;
                carte[i][j].type = VIDE;
                inukPresent = 1;
            }
        }
    }
    return inukPresent;
}
