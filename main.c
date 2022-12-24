#include "SDL_graphique.h"

int main(int argc, char *argv[])
{

monde_t monde;

monde.fin = false;


if(SDL_Init(SDL_INIT_VIDEO) < 0){ // Initialisation de la SDL
    printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
    SDL_Quit();
    return EXIT_FAILURE;
}


// Créer la fenêtre
monde.fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,
SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_RESIZABLE);
if(monde.fenetre == NULL){ // En cas d’erreur
    printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
    SDL_Quit();
    return EXIT_FAILURE;
}


// Mettre en place un contexte de rendu de l’écran
monde.ecran = SDL_CreateRenderer(monde.fenetre, -1, SDL_RENDERER_ACCELERATED);

//****Chargement image
//FOND
monde.fond = charger_image("../fond.bmp", monde.ecran);

//*****SPRITE JOUEUR
init_joueur(&monde.joueur);
monde.joueur.JoueurSprite = charger_image_transparente("../sprites.bmp", monde.ecran, 0, 255, 255); //Compteur pour réduire fréquence du mouvement du sprite du joueur


//**********OBSTACLE

monde.niveau.numero = 1;
monde.niveau.tabObstacle = chargerniveau(monde.niveau.numero, monde.ecran, &monde.niveau.nbObstacle);


// Boucle principale
while(!monde.fin){
    SDL_RenderClear(monde.ecran); //Clear la cible actuelle
    SDL_RenderCopy(monde.ecran, monde.fond, NULL, NULL); //Copie la texture et la met sur le renderer


    //Affichage graphique des obstacles du niveau
    for (int j=0; j<monde.niveau.nbObstacle; j++){
        SDL_RenderCopy(monde.ecran, monde.niveau.tabObstacle[j].TextureObstacle, NULL, &monde.niveau.tabObstacle[j].SpriteGraphique[0]);
        deplacementObstacle(&monde.niveau.tabObstacle[j]);
        if (sprites_collide(monde.joueur.SpriteGraphique, monde.niveau.tabObstacle[j].SpriteGraphique)){
            printf("touché\n");
        }
    }


    SDL_RenderCopy(monde.ecran, monde.joueur.JoueurSprite, &monde.joueur.SpriteFichier[0], &monde.joueur.SpriteGraphique[0]);

    //Animation du sprite Joueur
    if (monde.joueur.animation == true){
        monde.joueur.compteurSprite = animationJoueur(monde.joueur.compteurSprite, &monde.joueur.SpriteGraphique[0], &monde.joueur.SpriteFichier[0]); //Stockage de la valeur du compteur à chaque itération pour actualisation du sprite
    }
    JumpJoueur(&monde.joueur.jump, &monde.joueur, &monde.joueur.compteurJump, &monde.joueur.sensJump);


    SDL_PollEvent( &monde.evenements );
    handle_events(&monde.evenements, &monde.fin, &monde.joueur);

    //Update
    SDL_RenderPresent(monde.ecran);
}
// Quitter SDL
SDL_Quit();
SDL_DestroyTexture(monde.fond);
SDL_DestroyWindow(monde.fenetre);
return 0;
}