#include "SDL_donnees.h"


/**
 * @brief Initialiste le sprite du joueur à la bonne position avec l'animation prévue de base
 * 
 * @param DestR_JoueurSprite Axe y de l'image sprite pour afficher le sprite dans les bonnes dimensions
 * @param SrcR_JoueurSprite Axe x de l'image sprite pour afficher le sprite dasn les bonnes dimensions
 */
void InitSpriteJoueur(SDL_Rect* DestR_JoueurSprite, SDL_Rect* SrcR_JoueurSprite){
    DestR_JoueurSprite[0].x = PosXJoueur;
    DestR_JoueurSprite[0].y = PosYJoueur;
    DestR_JoueurSprite[0].w = 200/3; // Largeur du sprite
    DestR_JoueurSprite[0].h = 400/6; // Hauteur du sprite
    
    SrcR_JoueurSprite[0].y = 0;
    SrcR_JoueurSprite[0].x = 0; //%3 car il y a 3 sprites par ligne, quand on change de y, i%3=0 pour les 3 suivants
    SrcR_JoueurSprite[0].w = 200/3;
    SrcR_JoueurSprite[0].h = 400/6;
}


/**
 * @brief Fonction animant le sprite du joueur
 * 
 * @param compteSprite compteur, une fois atteint, changement de sprite (valeur arbitraite en constante)
 * @param DestR_JoueurSprite Axe y de l'image sprite pour afficher le sprite dans les bonnes dimensions
 * @param SrcR_JoueurSprite Axe x de l'image sprite pour afficher le sprite dasn les bonnes dimensions
 * @return int 
 */
int animationJoueur(int compteSprite, SDL_Rect* DestR_JoueurSprite, SDL_Rect* SrcR_JoueurSprite){
    if (compteSprite == CompteurSpriteJoueur){ //Nb arbitraite pour définir la vitesse de changement des sprites
        if (SrcR_JoueurSprite[0].x >= 200-((200/3)*2)){ //Si on est au dernier sprite à droite, alors on retourne à celui tout à gauche
            SrcR_JoueurSprite[0].x = 0;
        } else{
            SrcR_JoueurSprite[0].x += 200/3; //On passe au sprite suivant
        }
        compteSprite = 0; //Si on est à l'étape du changement, on réinstancie le compteur à 0
    } else{
        compteSprite += 1; 
    }
    return compteSprite;
}

/**
 * @brief initialise les paramètres du joueur
 * 
 * @param joueur le joueur
 */
void init_joueur(joueur_t* joueur){
    InitSpriteJoueur(&joueur->SpriteGraphique[0], &joueur->SpriteFichier[0]);
    joueur->compteurSprite = 0;
    joueur->sensJump = 0;
    joueur->jump = false;
    joueur->compteurJump = 0;
    joueur->animation = true;
}

void initObstacle(obstacle_t* obstacle, int x, int y, int w, int h, int v){
    obstacle->SpriteGraphique[0].x = x;
    obstacle->SpriteGraphique[0].y = y;
    obstacle->SpriteGraphique[0].w = w;
    obstacle->SpriteGraphique[0].h = h;
    obstacle->compteurVitesse = 0;
    obstacle->choc = false;
}



/**
 * @brief S'occupe de la gestion du saut du joueur
 * 
 * @param jump si false, le joueur n'est pas en train de sauter, si true, déclenchement de la fonction
 * @param joueur le joueur
 * @param compteurJump Compteur qui permet de ralentir la vitesse du saut (trop rapide avec juste des +1 et -1)
 * @param sens sens : 0 = vers le haut, 1 = vers le bas
 */
void JumpJoueur(bool* jump, joueur_t* joueur, int* compteurJump, int* sens){
    if (jump[0]==true){
        if (compteurJump[0] == CompteurJump){
            if (sens[0] == 0){
            joueur->SpriteGraphique[0].y -= 1;
            if (joueur->SpriteGraphique[0].y <=300){
                sens[0] = 1;
            }
            } else{
                joueur->SpriteGraphique[0].y += 1;
                if (joueur->SpriteGraphique[0].y ==400){
                    sens[0] = 0;
                    jump[0] = false;
                    joueur->animation = true;
                }
            }
            compteurJump[0] = 0;
        } else{
            compteurJump[0] +=1;
        }
    }
}

/**
 * @brief s'occupe de la gestion du clavier
 * 
 * @param evenements les evenements effectués(appuie touche/souris)
 * @param terminer jeu terminé ?
 * @param joueur le joueur
 */
void handle_events(SDL_Event* evenements, bool* terminer, joueur_t* joueur){
    switch(evenements->type){
        case SDL_QUIT:
            terminer[0] = true; break;
        case SDL_KEYUP:
            joueur->SpriteFichier[0].y = 0; //Si on relève la touche appuyé, ça remet le sprite de course de base
            break;
        case SDL_KEYDOWN:
            switch(evenements->key.keysym.sym){
                case SDLK_ESCAPE:
                terminer[0] = true; break;
                case SDLK_s: //Roulade, on met le sprite correspondant
                joueur->SpriteFichier[0].y = (400/6)*2; 
                break;
                case SDLK_a:
                joueur->SpriteFichier[0].y = 400 - 400/6;
                break;
                case SDLK_SPACE: //Permet d'éxécuter la fonction de saut à la prochaine boucle, et désactive l'animation du sprite
                joueur->jump = true;
                joueur->animation = false;
                break;
            } 
    }
}

/**
 * @brief déplace l'obstacle
 * 
 * @param obstacle 
 */

void deplacementObstacle(obstacle_t* obstacle){
    if (obstacle->compteurVitesse == CompteurObstacle){
        obstacle->SpriteGraphique[0].x -= 1;
        obstacle->compteurVitesse = 0;
    } else{
        obstacle->compteurVitesse += 1;
    }
}


/**
 * @brief cherche l'obstacle correspondant à partir du nom, et l'initialise
 * 
 * @param nomObstacle nom de l'obstacle
 * @param ecran  le renderer
 * @return l'obstacle initialisé
 */
obstacle_t TrouverObstacle(char nomObstacle[]){
    obstacle_t obstacle;
    if (strcmp(nomObstacle, "tronc1")==0){
        initObstacle(&obstacle, 1200, HauteurEcran-HauteurSol-40, 30, 40, 5);
    }
    return obstacle;
}