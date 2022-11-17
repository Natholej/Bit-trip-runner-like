#include "SDL_graphique.h"

int main(int argc, char *argv[])
{
SDL_Window* fenetre; // Déclaration de la fenêtre
SDL_Event evenements; // Événements liés à la fenêtre

bool terminer = false;

if(SDL_Init(SDL_INIT_VIDEO) < 0){ // Initialisation de la SDL
    printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
    SDL_Quit();
    return EXIT_FAILURE;
}


// Créer la fenêtre
fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,
SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_RESIZABLE);
if(fenetre == NULL){ // En cas d’erreur
    printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
    SDL_Quit();
    return EXIT_FAILURE;
}


// Mettre en place un contexte de rendu de l’écran
SDL_Renderer* ecran;
ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);

//****Chargement image
//FOND
SDL_Texture* fond = charger_image("../fond.bmp", ecran);



//*****SPRITE JOUEUR
SDL_Rect DestR_JoueurSprite[1];
SDL_Rect SrcR_JoueurSprite[1];

DestR_JoueurSprite[0].x = 50;
DestR_JoueurSprite[0].y = 300;
DestR_JoueurSprite[0].w = 285/3; // Largeur du sprite
DestR_JoueurSprite[0].h = 250/2; // Hauteur du sprite

SrcR_JoueurSprite[0].y = 0;
SrcR_JoueurSprite[0].x = 0; //%3 car il y a 3 sprites par ligne, quand on change de y, i%3=0 pour les 3 suivants
SrcR_JoueurSprite[0].w = 285/3;
SrcR_JoueurSprite[0].h = 250/2;

SDL_Texture* Joueursprite = charger_image_transparente("../sprites.bmp", ecran, 0, 255, 255);

int compteSprite = 0; //Compteur pour réduire fréquence du mouvement du sprite du joueur




// Boucle principale
while(!terminer){
    SDL_RenderClear(ecran); //Clear la cible actuelle
    SDL_RenderCopy(ecran, fond, NULL, NULL); //Copie la texture et la met sur le renderer


    SDL_RenderCopy(ecran, Joueursprite, &SrcR_JoueurSprite[0], &DestR_JoueurSprite[0]);
    if (compteSprite == 500){ //Nb arbitraite pour définir la vitesse de changement des sprites
        if (SrcR_JoueurSprite[0].x >= 285-(285/3)){ //Si on est au dernier sprite à droite, alors on retourne à celui tout à gauche
            SrcR_JoueurSprite[0].x = 0;
        }
        SrcR_JoueurSprite[0].x += 285/3; //On passe au sprite suivant
        compteSprite = 0; //Si on est à l'étape du changement, on réinstancie le compteur à 0
    } else{
        compteSprite += 1; 
    }
    

    SDL_PollEvent( &evenements );
    switch(evenements.type){
        case SDL_QUIT:
            terminer = true; break;
        case SDL_KEYDOWN:
            switch(evenements.key.keysym.sym){
                case SDLK_ESCAPE:
                case SDLK_q:
                terminer = true; break;
            }
    }

    //Update
    SDL_RenderPresent(ecran);
}
// Quitter SDL
SDL_Quit();
SDL_DestroyTexture(fond);
SDL_DestroyWindow(fenetre);
return 0;
}