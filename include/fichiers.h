/*
fichiers.h
----------

Par Deb0ch, grâce au site du zer0 !

Rôle: Gestion des fichiers: chargement et sauvegarde des niveaux, chargement images.

*/

#ifndef FICHIERS_H
#define FICHIERS_H

int chargerCarte(CASE_MAP carte[][NB_BLOCS_HAUTEUR] , int* lvlNum);
int sauverCarte(CASE_MAP carte[][NB_BLOCS_HAUTEUR] , SDL_Rect posInuk , int niveauActuel);
int nombreLignes(char* nomFichier);
int chargerImages(SDL_Surface*** images);
void release(SDL_Surface*** images);

#endif
