/*
fichiers.c
----------

Par Deb0ch, grâce au site du zer0 !

Rôle: Gestion des fichiers: chargement et sauvegarde des niveaux, chargement images.

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constantes.h"
#include "jeu.h"
#include "editeur.h"
#include "fichiers.h"




int chargerCarte(CASE_MAP carte[][NB_BLOCS_HAUTEUR] , int* lvlNum)
{ // On charge les éléments de la carte depuis un fichier texte, et on les stocke dans un tableau à deux dimensions de type CASE
    FILE* fichier;
    SDL_Rect posInuk; // La position du joueur n'est pas définie dans le tableau de cases mais par ses cordonnées sur la map
    int nbNiveaux , i = 1 , j;
    char c;

    nbNiveaux = nombreLignes(NOM_FICHIER); // On obtient le nombre de niveaux dans le fichier

    if(*lvlNum > nbNiveaux) // On ajuste le numéro du niveau demandé si celui-ci est trop grand/petit
        *lvlNum = nbNiveaux;
    if(*lvlNum < 1)
        *lvlNum = 1;

    fichier = fopen(NOM_FICHIER , "r");
    if(fichier == NULL)
      return 0;

    while(i != *lvlNum)
      { // Et on se positionne au bon endroit dans le fichier
        do {
	  c = fgetc(fichier);
        } while(c != '\n' && c != EOF);
        ++i;
      }

    if(!(fscanf(fichier , "%d" , &posInuk.x))) // Si il n'y a rien d'écrit dans le fichier texte on met par défaut la case à VIDE et sans graphisme plutot que de faire planter le programme
        posInuk.x = -1; // Les  premiers caractères de la ligne sont la position du joueur, -1 -1 si joueur absent
    if(!(fscanf(fichier , "%d" , &posInuk.y)))
        posInuk.y = -1;

    fgetc(fichier);

    for(i = 0 ; i < NB_BLOCS_LARGEUR ; ++i){
        for(j = 0 ; j < NB_BLOCS_HAUTEUR ; ++j){

            if(!(fscanf(fichier , "%d" , &carte[i][j].type))) // Et la, si il n'y a rien d'écrit dans le fichier texte on met par défaut la case à VIDE et sans graphisme plutot que de faire planter le programme
                carte[i][j].type = VIDE;
            if(!(fscanf(fichier , "%d" , &carte[i][j].graphisme)))
                carte[i][j].graphisme = NONE;
        }
    }
    if(posInuk.x != -1 && posInuk.y != -1)
        carte[posInuk.x][posInuk.y].type = INUK; // Vu que la fonction ne renvoie que le tableau de cases, on stocke le personnage dedans à ses coordonnées.

    fclose(fichier);
    return 1;
}

int sauverCarte(CASE_MAP carte[][NB_BLOCS_HAUTEUR] , SDL_Rect posInuk , int niveauActuel){ // Enregistre la carte qu'on vient d'éditer avec l'éditeur de niveaux. La carte enregistrée remplace sa version précédente dans le fichier.
/* On procède en stockant les n - 1 premiers niveaux dans une chaîne, en stockant le niveau
que l'on souhaite enregistrer à la suite de la chaîne, puis en copiant les n + 1 derniers
niveaux à la suite. On écrit ensuite la chaîne dans le fichier. */
    FILE *fichier = NULL;
    char *niveaux, tmp[TAILLE_NIVEAU];
    int i = 1 , j;

    fichier = fopen(NOM_FICHIER, "r+");
    if(fichier == NULL){
#ifdef WIN32
        MessageBox(0 , "Ouverture du fichier niveaux échouée lors de la sauvegarde" , "ERREUR" , MB_ICONEXCLAMATION);
#else
		printf("Ouverture du fichier niveaux échouée lors de la sauvegarde\n");
#endif
            fprintf(stderr , "Ouverture du fichier niveaux échouée lors de la sauvegarde\n");
            return 0;
    }

    niveaux = malloc((nombreLignes(NOM_FICHIER) * TAILLE_NIVEAU + 1) * sizeof(char)); // DEBUT Allocation pour niveaux, qui contiendra les niveaux sous forme de chaine de caractères
    if(niveaux == NULL){
#ifdef WIN32
        MessageBox(0 , "Allocation de mémoire échouée lors de la sauvegarde" , "ERREUR" , MB_ICONEXCLAMATION);
#else
		printf("Allocation de mémoire échouée lors de la sauvegarde\n");
#endif
            fprintf(stderr , "Allocation de mémoire échouée lors de la sauvegarde\n");
            return 0;
    }                                                                   // FIN de première allocation

    memset (niveaux , 0 , sizeof (niveaux));

    for(i = 1 ; i < niveauActuel ; ++i){ // On copie les niveauActuel - 1 premiers niveaux dans une chaine de caracteres de longueur extensible

        fgets(tmp , TAILLE_NIVEAU + 1 , fichier);
        strcat(niveaux , tmp);
    }

    sprintf(tmp , "%d " , posInuk.x);   // On copie le niveau actuel
    strcat(niveaux , tmp);
    sprintf(tmp , "%d " , posInuk.y);
    strcat(niveaux , tmp);

    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++){
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++){

            sprintf(tmp, "%d ", carte[i][j].type);
            strcat(niveaux , tmp);
            sprintf(tmp, "%d ", carte[i][j].graphisme);
            strcat(niveaux , tmp);
        }
    }

    sprintf(tmp , "\n");
    strcat(niveaux , tmp);

    fgets(tmp , TAILLE_NIVEAU + 1 , fichier); // On "saute" le n-ième niveau

    for(i = niveauActuel + 1 ; i <= nombreLignes(NOM_FICHIER) ; ++i){ // On copie les niveaux restants dans la chaine
        fgets(tmp , TAILLE_NIVEAU + 1 , fichier);
        strcat(niveaux , tmp);
    }

    fclose(fichier);

    fichier = fopen(NOM_FICHIER , "w"); // On écrase le contenu du fichier plutôt que de faire un simple rewind, c'est plus sûr.
    if(fichier == NULL){
#ifdef WIN32
        MessageBox(0 , "Ecrasement du fichier niveaux échouée lors de la sauvegarde" , "ERREUR" , MB_ICONEXCLAMATION);
#else
		printf("Ecrasement du fichier niveaux échouée lors de la sauvegarde\n");
#endif
            fprintf(stderr , "Ecrasement du fichier niveaux échouée lors de la sauvegarde\n");
            return 0;
    }

    fprintf(fichier , "%s" , niveaux); // Et on copie la chaîne dans le fichier

    fclose(fichier);

    return 1;
}

int creerCarte(CASE_MAP carte[][NB_BLOCS_HAUTEUR] , int *niveauActuel){ // Enregistre la carte qu'on vient d'éditer avec l'éditeur de niveaux.

    FILE* fichier = NULL;
    char c;
    int i = 1, j;

    fichier = fopen(NOM_FICHIER, "a");
    if (fichier == NULL)
        return 0;

    fprintf(fichier , "-1 ");
    fprintf(fichier , "-1 ");

    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++){
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++){

            fprintf(fichier , "0 ");
            fprintf(fichier , "0 ");
        }
    }

    fputc('\n' , fichier);

    fclose(fichier);

    *niveauActuel = nombreLignes(NOM_FICHIER);

    return 1;
}

int nombreLignes(char* nomFichier){

    FILE* fichier = NULL;
    char c;
    int nbLignes = 0;

    fichier = fopen(nomFichier , "r");
    if (fichier == NULL)
      return 0;

    while((c = fgetc(fichier)) != EOF){
      if(c == '\n')
	nbLignes += 1;
    }

    fclose(fichier);

    return nbLignes;
}

int chargerImages(SDL_Surface*** images){ // Charge toutes les images utilisées dans le jeu dans un tableau de SDL_Surface* .

    int i;

    *images = malloc(GRAPHISME_LAST * sizeof(SDL_Surface*));
    if(images == NULL){
#ifdef WIN32
        MessageBox(0 , "Allocation de mémoire échouée lors du chargement des images" , "ERREUR" , MB_ICONEXCLAMATION);
#else
		printf("Allocation de mémoire échouée lors du chargement des images\n");
#endif
            fprintf(stderr , "Allocation de mémoire échouée lors du chargement des images\n");
            return -1;
    }

    (*images)[MUR_BORDH] =              IMG_Load("sprites/mur_bordh.bmp");
    (*images)[MUR_BORDB] =              IMG_Load("sprites/mur_bordb.bmp");
    (*images)[MUR_BORDG] =              IMG_Load("sprites/mur_bordg.bmp");
    (*images)[MUR_BORDD] =              IMG_Load("sprites/mur_bordd.bmp");
    (*images)[MUR_COINHG] =             IMG_Load("sprites/mur_coinhg.bmp");
    (*images)[MUR_COINHD] =             IMG_Load("sprites/mur_coinhd.bmp");
    (*images)[MUR_COINBG] =             IMG_Load("sprites/mur_coinbg.bmp");
    (*images)[MUR_COINBD] =             IMG_Load("sprites/mur_coinbd.bmp");
    (*images)[MUR_COINHGB] =            IMG_Load("sprites/mur_coinhgb1.bmp");
    (*images)[MUR_COINHDB] =            IMG_Load("sprites/mur_coinhdb1.bmp");
    (*images)[MUR_COINHGB2] =           IMG_Load("sprites/mur_coinhgb2.bmp");
    (*images)[MUR_COINHDB2] =           IMG_Load("sprites/mur_coinhdb2.bmp");
    (*images)[MUR_COINBGB] =            IMG_Load("sprites/mur_coinbgb.bmp");
    (*images)[MUR_COINBDB] =            IMG_Load("sprites/mur_coinbdb.bmp");
    (*images)[MUR_BLOC1] =              IMG_Load("sprites/mur_bloc_neige.bmp");
    (*images)[MUR_CAILLOU_GLACE] =      IMG_Load("sprites/mur_caillou_glace.bmp");
    (*images)[MUR_CAILLOU_SOL1] =       IMG_Load("sprites/mur_caillou_sol1.bmp");
    (*images)[MUR_CAILLOU_GLACEB] =     IMG_Load("sprites/mur_caillou_glaceb.bmp");
    (*images)[SOL_GLACE] =              IMG_Load("sprites/sol_glace.bmp");
    (*images)[SOL_GLACE_FISSURE] =      IMG_Load("sprites/sol_glace_fissure.bmp");
    (*images)[SOL_SOL2] =               IMG_Load("sprites/sol_sol1.bmp");
    (*images)[SOL_ESCALIER_HAUT] =      IMG_Load("sprites/sol_escalier_haut.bmp");
    (*images)[SOL_ESCALIER_BAS] =       IMG_Load("sprites/sol_escalier_bas.bmp");
    (*images)[SOL_ESCALIER_GAUCHE] =    IMG_Load("sprites/sol_escalier_gauche.bmp");
    (*images)[SOL_ESCALIER_DROITE] =    IMG_Load("sprites/sol_escalier_droite.bmp");
    (*images)[OBJ_TROU_SOL1] =          IMG_Load("sprites/trou_glace.png");
    (*images)[OBJ_TROU_SOL2] =          IMG_Load("sprites/trou_sol1.png");
    (*images)[CAISSE_BOIS] =            IMG_Load("sprites/caisse_bois.bmp");
    (*images)[CAISSE_BOISOK] =          IMG_Load("sprites/caisse_boisOK.bmp");
    (*images)[INUK_HAUT] =              IMG_Load("sprites/inuk_haut.png");
    (*images)[INUK_BAS] =               IMG_Load("sprites/inuk_bas.png");
    (*images)[INUK_GAUCHE] =            IMG_Load("sprites/inuk_gauche.png");
    (*images)[INUK_DROITE] =            IMG_Load("sprites/inuk_droite.png");
    (*images)[MENU_BRAVO] =             IMG_Load("sprites/continue.png");

    for(i = 0 ; i < GRAPHISME_LAST ; ++i){
        if((*images)[i] == NULL){
#ifdef WIN32
        MessageBox(0 , "Une erreur est survenue lors du chargement des images" , "ERREUR" , MB_ICONEXCLAMATION);
#else
	printf("Une erreur est survenue lors du chargement des images : %d\n", i);
#endif
            fprintf(stderr, "Une erreur est survenue lors du chargement des images : %d\n", i);
            return -1;
        }
    }

    return 0;
}

void release(SDL_Surface*** images){ // Libère la mémoire des images après utilisation.

    int i;

    for(i = 1 ; i < GRAPHISME_LAST ; ++i)
        SDL_FreeSurface((*images)[i]);

    free(*images);
}
