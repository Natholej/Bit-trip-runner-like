#include "SDL_graphique.h"

int main(int argc, char *argv[])
{
SDL_Window* fenetre; // Déclaration de la fenêtre
SDL_Event evenements; // Événements liés à la fenêtre

bool terminer = false;

int compteur = 0;


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
joueur_t joueur;
init_joueur(&joueur);
joueur.JoueurSprite = charger_image_transparente("../sprites.bmp", ecran, 0, 255, 255); //Compteur pour réduire fréquence du mouvement du sprite du joueur

// Boucle principale
while(!terminer){
    SDL_RenderClear(ecran); //Clear la cible actuelle
    SDL_RenderCopy(ecran, fond, NULL, NULL); //Copie la texture et la met sur le renderer


    SDL_RenderCopy(ecran, joueur.JoueurSprite, &joueur.SpriteFichier[0], &joueur.SpriteGraphique[0]);

    //Animation du sprite Joueur
    if (joueur.animation == true){
        joueur.compteurSprite = animationJoueur(joueur.compteurSprite, &joueur.SpriteGraphique[0], &joueur.SpriteFichier[0]); //Stockage de la valeur du compteur à chaque itération pour actualisation du sprite
    }

    JumpJoueur(&joueur.jump, &joueur, &joueur.compteurJump, &joueur.sensJump);


    SDL_PollEvent( &evenements );
    handle_events(&evenements, &terminer, &joueur);

    //Update
    SDL_RenderPresent(ecran);
}
// Quitter SDL
SDL_Quit();
SDL_DestroyTexture(fond);
SDL_DestroyWindow(fenetre);
return 0;
}