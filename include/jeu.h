/*
jeu.c
------

Par Deb0ch, grâce au site du zer0 !

Rôle: Le codage du jeu en lui même, fonctions relatives au jeu et à l'affichage de l'écran.

*/


#ifndef JEU_H
#define JEU_H

void jeu(SDL_Surface* ecran); // La fonction gérant une partie
void deplacerJoueur(CASE_MAP carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction); // Déplace le joueur si c'est possible (gestion des collisions)
void deplacerCaisse(int *case1 , int *case2); // Déplace une caisse de la position d'origine à la position de départ
int rafraichirCarte(CASE_MAP carte[][NB_BLOCS_HAUTEUR] , SDL_Surface*** images , SDL_Surface* ecran , SDL_Rect* inuk , SDL_Surface* inukActuel); // Remplit l'écran avec les éléments de la map et blitte le joueur par dessus. Le SDL_Flip ne se fait pas dans la fonction. Renvoie 0 si aucun objectif n'est affiché, 1 sinon.
int detecterJoueur(CASE_MAP carte[][NB_BLOCS_HAUTEUR] , SDL_Rect* positionJoueur); // Renvoie 1 si le joueur est présent, 0 sinon. Si le joueur est présent, ses coordonnées sont écrites dans la variabe positionJoueur.

#endif
