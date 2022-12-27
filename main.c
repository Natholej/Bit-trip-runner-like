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
        //Si estDetruit est true, la texture ne se raffraichira pas donc il ne sera plus affiché
        if (monde->niveau.tabObstacle[j].estDetruit== false){
            SDL_RenderCopy(monde->ecran, monde->niveau.tabObstacle[j].TextureObstacle, NULL, &monde->niveau.tabObstacle[j].SpriteGraphique[0]);
        }
        deplacementObstacle(&monde->niveau.tabObstacle[j]);
        if (monde->joueur.roulade){
            bonusroulade = JoueurH- JoueurHenRoulade;
        } else{
            bonusroulade = 0;
        }
        //Si collision et obstacle pas cassé, retour au début du niveau
        if (sprites_collide(monde->joueur.SpriteGraphique, monde->niveau.tabObstacle[j].SpriteGraphique, bonusroulade) && monde->niveau.tabObstacle[j].estDetruit == false){
            if (monde->joueur.CoupDePied == true && monde->niveau.tabObstacle[j].peutEtrecasse == true){
            monde->niveau.tabObstacle[j].estDetruit = true;
            } else{
                monde->niveau.tabObstacle = chargerniveau(monde->niveau.numero, monde->ecran, &monde->niveau.nbObstacle);
            }
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
void handle_choix(int* choix, niveau_t* niveau, SDL_Renderer* ecran, bool* terminer){
    if (choix[0]==1){
        niveau->numero = 1;
        niveau->tabObstacle = chargerniveau(niveau->numero, ecran, &niveau->nbObstacle);
    } if(choix[0]==2){
        niveau->numero = 2;
        niveau->tabObstacle = chargerniveau(niveau->numero, ecran, &niveau->nbObstacle);
    } if (choix[0]==3){
        niveau->numero = 3;
        niveau->tabObstacle = chargerniveau(niveau->numero, ecran, &niveau->nbObstacle);
    } if (choix[0]==5){
        terminer[0] = true;
    }
}


int main(int argc, char *argv[])
{

monde_t monde;


SDL_Init(SDL_INIT_VIDEO);

initMonde(&monde);

initTexture(&monde);



// Boucle principale
while(!monde.fin){
    SDL_RenderClear(monde.ecran); //Clear la cible actuelle
    SDL_RenderCopy(monde.ecran, monde.fond, NULL, NULL); //Copie la texture et la met sur le renderer


    if (!monde.pause){
        update_data(&monde);
        victoire(&monde.niveau, &monde.pause, monde.ecran);
    } else{
        handle_pause(&monde.joueur, &monde.menu, monde.ecran);
    }

    //Animation du sprite Joueur
    if (monde.joueur.animation == true){
        monde.joueur.compteurSprite = animationJoueur(monde.joueur.compteurSprite, &monde.joueur.SpriteGraphique[0], &monde.joueur.SpriteFichier[0]); //Stockage de la valeur du compteur à chaque itération pour actualisation du sprite
    }

    SDL_RenderCopy(monde.ecran, monde.joueur.JoueurSprite, &monde.joueur.SpriteFichier[0], &monde.joueur.SpriteGraphique[0]);


    SDL_PollEvent( &monde.evenements );
    handle_events(&monde.evenements, &monde.fin, &monde.joueur, &monde.pause, &monde.menu.choix, &monde.niveau, monde.ecran, &monde.joueur.roulade, &monde.menu.souris);

    //Update
    SDL_RenderPresent(monde.ecran);
}
// Quitter SDL
SDL_Quit();
SDL_DestroyTexture(monde.fond);
SDL_DestroyWindow(monde.fenetre);
return 0;
}