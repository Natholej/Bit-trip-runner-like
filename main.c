#include "SDL_graphique.h"

/**
 * @brief rafraichît les données utiles à l'éxécution du jeu lorsque celui-ci n'est pas en pause
 * 
 * @param monde le monde
 */
void update_data(monde_t* monde){
    //Affichage graphique des obstacles du niveau
    int bonusroulade;
    for (int j=0; j<monde->niveau.nbObstacle; j++){
        SDL_RenderCopy(monde->ecran, monde->niveau.tabObstacle[j].TextureObstacle, NULL, &monde->niveau.tabObstacle[j].SpriteGraphique[0]);
        deplacementObstacle(&monde->niveau.tabObstacle[j]);
        if (monde->joueur.roulade){
            bonusroulade = JoueurH- JoueurHenRoulade;
        } else{
            bonusroulade = 0;
        }
        if (sprites_collide(monde->joueur.SpriteGraphique, monde->niveau.tabObstacle[j].SpriteGraphique, bonusroulade)){
            monde->niveau.tabObstacle = chargerniveau(monde->niveau.numero, monde->ecran, &monde->niveau.nbObstacle);
        }
    }
    JumpJoueur(&monde->joueur.jump, &monde->joueur, &monde->joueur.compteurJump, &monde->joueur.sensJump);
}

/**
 * @brief s'occupe des conséquences des différents choix fait par le jour dans le menu
 * 
 * @param choix int contenant le choix (de 1 à 5)
 * @param niveau le niveau, qui sera initialisé
 * @param ecran l'écran -> le rendu
 */
void handle_choix(int* choix, niveau_t* niveau, SDL_Renderer* ecran){
    if (choix[0]==1){
        niveau->numero = 1;
        niveau->tabObstacle = chargerniveau(niveau->numero, ecran, &niveau->nbObstacle);
    }
}


int main(int argc, char *argv[])
{

monde_t monde;

monde.fin = false;
monde.pause = true;
monde.menu.choix = 1;


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
//MENU (test à mettre dans une fonction)
monde.menu.texturemenu = charger_image_transparente("../Menu.bmp", monde.ecran, 0, 255, 0);
//FLECHE MENU
monde.menu.curseur = charger_image("../curseur.bmp", monde.ecran);

monde.menu.placecurseur[0].x = 600;
monde.menu.placecurseur[0].y = 50;
monde.menu.placecurseur[0].w = 50;
monde.menu.placecurseur[0].h = 50;

//*****SPRITE JOUEUR
init_joueur(&monde.joueur);
monde.joueur.JoueurSprite = charger_image_transparente("../sprites.bmp", monde.ecran, 0, 255, 255); //Compteur pour réduire fréquence du mouvement du sprite du joueur



// Boucle principale
while(!monde.fin){
    SDL_RenderClear(monde.ecran); //Clear la cible actuelle
    SDL_RenderCopy(monde.ecran, monde.fond, NULL, NULL); //Copie la texture et la met sur le renderer


    if (!monde.pause){
        update_data(&monde);
    } else{
        handle_pause(&monde);
    }

    //Animation du sprite Joueur
    if (monde.joueur.animation == true){
        monde.joueur.compteurSprite = animationJoueur(monde.joueur.compteurSprite, &monde.joueur.SpriteGraphique[0], &monde.joueur.SpriteFichier[0]); //Stockage de la valeur du compteur à chaque itération pour actualisation du sprite
    }

    SDL_RenderCopy(monde.ecran, monde.joueur.JoueurSprite, &monde.joueur.SpriteFichier[0], &monde.joueur.SpriteGraphique[0]);


    SDL_PollEvent( &monde.evenements );
    handle_events(&monde.evenements, &monde.fin, &monde.joueur, &monde.pause, &monde.menu.choix, &monde.niveau, monde.ecran, &monde.joueur.roulade);

    //Update
    SDL_RenderPresent(monde.ecran);
}
// Quitter SDL
SDL_Quit();
SDL_DestroyTexture(monde.fond);
SDL_DestroyWindow(monde.fenetre);
return 0;
}