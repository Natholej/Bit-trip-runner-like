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
                monde->niveau.score = 0;
                monde->ScoreActuelle = -1;
                monde->niveau.tabObstacle = chargerniveau(&monde->niveau.numero, monde->ecran, &monde->niveau.nbObstacle, &monde->niveau.score);
            }
        }
    }
    //Gestion du saut du joueur
    JumpJoueur(&monde->joueur.jump, &monde->joueur, &monde->joueur.compteurJump, &monde->joueur.sensJump);

    //Pour le mode arcade, génération d'un nouvel obstacle à chaque fois
    if (monde->niveau.numero==4){
        for (int i=0; i<monde->niveau.nbObstacle; i++){
            if (monde->niveau.tabObstacle[i].SpriteGraphique[0].x <0){
                char* obst = trouverStringObstacle(rand()%4);
                monde->niveau.tabObstacle[i] = TrouverObstacle(obst, PosPremierObstacleNiveau);
                if (strcmp(obst,"troncCassable")==0){ //Si c'est le troncCassable, on charge l'image qui correspond, différente des autres (rouge)
                    monde->niveau.tabObstacle[i].TextureObstacle = charger_image("../Ressources/TroncCassable.bmp", monde->ecran);
                } else{
                    monde->niveau.tabObstacle[i].TextureObstacle = charger_image("../Ressources/Tronc.bmp", monde->ecran);
                }

                monde->niveau.score +=1 ;
            }
        }
    }
}

/**
 * @brief s'occupe des conséquences des différents choix fait par le jour dans le menu
 * 
 * @param choix int contenant le choix (de 1 à 5)
 * @param niveau le niveau, qui sera initialisé
 * @param ecran l'écran -> le rendu
 * @param terminer jeu terminé ?
 * @param pause jeu en pause ?
 * @param niveauAccompli nombre de niveau accompli
 */
void handle_choix(int* choix, niveau_t* niveau, SDL_Renderer* ecran, bool* terminer, bool* pause, int* niveauAccompli){
    if (choix[0]==1){
        niveau->numero = 1;
        niveau->tabObstacle = chargerniveau(&niveau->numero, ecran, &niveau->nbObstacle, &niveau->score);
        pause[0] = false;
    } if(choix[0]==2 && niveauAccompli[0]>=1){
        niveau->numero = 2;
        niveau->tabObstacle = chargerniveau(&niveau->numero, ecran, &niveau->nbObstacle, &niveau->score);
        pause[0] = false;
    } if (choix[0]==3 && niveauAccompli[0]>=2){
        niveau->numero = 3;
        niveau->tabObstacle = chargerniveau(&niveau->numero, ecran, &niveau->nbObstacle, &niveau->score);
        pause[0] = false;
    } if (choix[0]==4){
        niveau->numero = 4;
        niveau->tabObstacle = chargerniveau(&niveau->numero, ecran, &niveau->nbObstacle, &niveau->score);
        pause[0] = false;
    } if (choix[0]==5){
        terminer[0] = true;
    }
}


int main(int argc, char *argv[])
{

srand(time(NULL));

monde_t monde;


SDL_Init(SDL_INIT_VIDEO);

initMonde(&monde);

initTexture(&monde);


// Initialise SDL_ttf, elle retourne -1 s’il y a une erreur
int TTF_Init( ) ;
TTF_Init();
TTF_Font *font = TTF_OpenFont("../Ressources/Minecraft.ttf",28);
SDL_Color color = {255,255,255};
SDL_Rect text_pos; // Position du texte
text_pos.x = 10;
text_pos.y = 0;
text_pos.w = 250; // Largeur du texte en pixels (à récupérer)
text_pos.h = 100; // Hauteur du texte en pixels (à récupérer)

SDL_Texture* texte; //= SDL_CreateTextureFromSurface(monde.ecran, surface);
char score[20];
sprintf(score, "Score : %d", monde.niveau.score);
SDL_Surface* surface = TTF_RenderText_Solid(font, score, color);
texte = SDL_CreateTextureFromSurface(monde.ecran, surface);




// Boucle principale
while(!monde.fin){
    SDL_RenderClear(monde.ecran); //Clear la cible actuelle
    SDL_RenderCopy(monde.ecran, monde.fond, NULL, NULL); //Copie la texture et la met sur le renderer

    
    if (monde.niveau.numero==4){
        if (monde.ScoreActuelle < monde.niveau.score){ //Dédoublement du score pour limiter le rafraichissement du score et ne pas provoquer un problème de mémoire
        monde.ScoreActuelle = monde.niveau.score;

        char score[10];
        sprintf(score, "Score : %d", monde.niveau.score);
        SDL_Surface* surface = TTF_RenderText_Solid(font, score, color);
        texte = SDL_CreateTextureFromSurface(monde.ecran, surface);
        }
        SDL_RenderCopy(monde.ecran,texte,NULL, &text_pos); 
    }




    if (!monde.pause){
        update_data(&monde);
        victoire(&monde.niveau, &monde.pause, monde.ecran, &monde.niveauAccompli);
    } else{
        handle_pause(&monde.joueur, &monde.menu, monde.ecran);
    }

    //Animation du sprite Joueur
    if (monde.joueur.animation == true){
        monde.joueur.compteurSprite = animationJoueur(monde.joueur.compteurSprite, &monde.joueur.SpriteGraphique[0], &monde.joueur.SpriteFichier[0]); //Stockage de la valeur du compteur à chaque itération pour actualisation du sprite
    }

    SDL_RenderCopy(monde.ecran, monde.joueur.JoueurSprite, &monde.joueur.SpriteFichier[0], &monde.joueur.SpriteGraphique[0]);


    SDL_PollEvent( &monde.evenements );
    handle_events(&monde.evenements, &monde.fin, &monde.joueur, &monde.pause, &monde.menu.choix, &monde.niveau, monde.ecran, &monde.joueur.roulade, &monde.menu.souris, &monde.niveauAccompli);

    //Update
    SDL_RenderPresent(monde.ecran);
}

// Fermer la police et quitter SDL_ttf
TTF_CloseFont( font );
TTF_Quit(); 


// Quitter SDL
SDL_Quit();
SDL_DestroyTexture(monde.fond);
SDL_DestroyTexture(monde.joueur.JoueurSprite);
SDL_DestroyTexture(monde.niveau.victoire);
SDL_DestroyTexture(monde.menu.texturemenu);
SDL_DestroyTexture(monde.menu.curseur);
SDL_DestroyWindow(monde.fenetre);
return 0;
}