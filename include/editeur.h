/*
editeur.h
----------

Par Deb0ch, gr�ce au site du zer0 !

R�le: Editeur de niveaux

*/

#ifndef EDITEUR_H
#define EDITEUR_H

void editeur(SDL_Surface* ecran);
void poserObjet(CASE_MAP* caseActuelle , SDL_Rect coordActuelles , CASE_MAP objetActuel , SDL_Rect* posInuk);

#endif
