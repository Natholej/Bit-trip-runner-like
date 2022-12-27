#include "SDL_graphique.h"



/**
 * @brief Charge une image
 * 
 * @param nomfichier nom de l'image
 * @param renderer le renderer
 * @return SDL_Texture* Texture SDL nécessaire à l'affichage
 */
SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer* renderer){
    SDL_Surface *surface = SDL_LoadBMP(nomfichier) ;
    return SDL_CreateTextureFromSurface(renderer, surface);

}

/**
 * @brief Charge une image transparente
 * 
 * @param nomfichier nom de l'image
 * @param renderer le renderer
 * @param r code rouge de la couleur à effacer
 * @param g code vert de la couleur à effacer
 * @param b code bleu de la couleur à effacer
 * @return SDL_Texture* Texture SDL nécessaire à l'affichage
 */
SDL_Texture* charger_image_transparente(const char* nomfichier, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b){
    SDL_Surface* surface = SDL_LoadBMP(nomfichier);
    SDL_PixelFormat* fmt = surface->format;
    Uint32 rgb = SDL_MapRGB(fmt, r, g, b);
    SDL_SetColorKey(surface, SDL_TRUE, rgb);
    return SDL_CreateTextureFromSurface(renderer, surface);
}


/**
 * @brief Charge les obstacles du niveau selon celui choisit
 * 
 * @param niveau numéro du niveau
 * @param ecran le renderer
 * @param nbObstacle le nombre d'obstacle (qu'on récupèrera pour la boucle principale du jeu)
 * @return le tableau contenat les obstacles 
 */
obstacle_t* chargerniveau(int niveau, SDL_Renderer* ecran, int* nbObstacle){
    obstacle_t* tabObstacle;
    if (niveau==1){
        nbObstacle[0] = 5; //On le définit pour le récupérer en dehors de la fonction
        tabObstacle = malloc(sizeof(obstacle_t)*nbObstacle[0]);
        char* tabString[nbObstacle[0]]; 
        tabString[0] = "tronc1";
        tabString[1] = "tronc2";
        tabString[2] = "tronc1";
        tabString[3] = "tronc2";
        tabString[4] = "tronc2";

        int posX = 1200; //position du premier obstacle définit arbitrairement

        for (int i=0; i<nbObstacle[0]; i++){
            tabObstacle[i] = TrouverObstacle(tabString[i], posX); //on trouve l'obstacle correspondant et le positionne à x = posX;
            if (strcmp(tabString[i],"tronc4")==0){ //Si c'est le tronc4, on charge l'image qui correspond
                tabObstacle[i].TextureObstacle = charger_image("../TroncCassable.bmp", ecran);
            } else{ //Si c'est pas le 4, alors ils ont tous la même base
                tabObstacle[i].TextureObstacle = charger_image("../Tronc.bmp", ecran);
            }
            posX += 500;
        }
    } else{
        if (niveau==2){
            nbObstacle[0] = 8; //On le définit pour le récupérer en dehors de la fonction
            tabObstacle = malloc(sizeof(obstacle_t)*nbObstacle[0]);
            char* tabString[nbObstacle[0]]; 
            tabString[0] = "tronc2";
            tabString[1] = "tronc2";
            tabString[2] = "tronc3";
            tabString[3] = "tronc1";
            tabString[4] = "tronc3";
            tabString[5] = "tronc1";
            tabString[6] = "tronc2";
            tabString[7] = "tronc3";

            int posX = 1200; //position du premier obstacle définit arbitrairement

            for (int i=0; i<nbObstacle[0]; i++){
                tabObstacle[i] = TrouverObstacle(tabString[i], posX); //on trouve l'obstacle correspondant et le positionne à x = posX;
                if (strcmp(tabString[i],"tronc4")==0){ //Si c'est le tronc4, on charge l'image qui correspond
                    tabObstacle[i].TextureObstacle = charger_image("../TroncCassable.bmp", ecran);
                } else{
                    tabObstacle[i].TextureObstacle = charger_image("../Tronc.bmp", ecran);
                }
                posX += 400;
            }
        } else{
            if (niveau==3){
                nbObstacle[0] = 10; //On le définit pour le récupérer en dehors de la fonction
                tabObstacle = malloc(sizeof(obstacle_t)*nbObstacle[0]);
                char* tabString[nbObstacle[0]]; 
                tabString[0] = "tronc2";
                tabString[1] = "tronc4";
                tabString[2] = "tronc3";
                tabString[3] = "tronc1";
                tabString[4] = "tronc3";
                tabString[5] = "tronc4";
                tabString[6] = "tronc2";
                tabString[7] = "tronc3";
                tabString[8] = "tronc1";
                tabString[9] = "tronc4";

                int posX = 1200; //position du premier obstacle définit arbitrairement

                for (int i=0; i<nbObstacle[0]; i++){
                    tabObstacle[i] = TrouverObstacle(tabString[i], posX); //on trouve l'obstacle correspondant et le positionne à x = posX;
                    if (strcmp(tabString[i],"tronc4")==0){ //Si c'est le tronc4, on charge l'image qui correspond
                        tabObstacle[i].TextureObstacle = charger_image("../TroncCassable.bmp", ecran);
                    } else{
                        tabObstacle[i].TextureObstacle = charger_image("../Tronc.bmp", ecran);
                    }
                    posX += 300;
                }
            }
        }
    }
    return tabObstacle;

}
