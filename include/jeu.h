/*
jeu.c
------

Par Deb0ch, gr�ce au site du zer0 !

R�le: Le codage du jeu en lui m�me, fonctions relatives au jeu et � l'affichage de l'�cran.

*/


#ifndef JEU_H
#define JEU_H

void jeu(SDL_Surface* ecran); // La fonction g�rant une partie
void deplacerJoueur(CASE_MAP carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction); // D�place le joueur si c'est possible (gestion des collisions)
void deplacerCaisse(int *case1 , int *case2); // D�place une caisse de la position d'origine � la position de d�part
int rafraichirCarte(CASE_MAP carte[][NB_BLOCS_HAUTEUR] , SDL_Surface*** images , SDL_Surface* ecran , SDL_Rect* inuk , SDL_Surface* inukActuel); // Remplit l'�cran avec les �l�ments de la map et blitte le joueur par dessus. Le SDL_Flip ne se fait pas dans la fonction. Renvoie 0 si aucun objectif n'est affich�, 1 sinon.
int detecterJoueur(CASE_MAP carte[][NB_BLOCS_HAUTEUR] , SDL_Rect* positionJoueur); // Renvoie 1 si le joueur est pr�sent, 0 sinon. Si le joueur est pr�sent, ses coordonn�es sont �crites dans la variabe positionJoueur.

#endif
