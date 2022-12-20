#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>

#define CompteurSpriteJoueur 200

#define CompteurJump 5
#define CompteurObstacle 3

#define PosXJoueur 100
#define PosYJoueur 400

#define HauteurSol 255

#define HauteurEcran 720
#define LargeurEcran 1280

struct joueur{
    SDL_Rect SpriteGraphique[1]; //Position du joueur sur la carte
    SDL_Rect SpriteFichier[1]; //Position du sprite du joueur dans le fichier
    SDL_Texture* JoueurSprite; //Texture du joueur
    int compteurSprite; //Compteur pour contrôler la vitesse de défilement des images du sprite
    int sensJump; // Sens du saut (d'abord monter puis descendre);
    int compteurJump; //Compteur pour contrôler la vitesse du saut
    bool jump; //Est-ce que le joueur saute ?
    bool animation; //Activer/désactiver l'animation du joueur
};

typedef struct joueur joueur_t;

struct obstacle{
    SDL_Rect SpriteGraphique[1]; //Position du sprite sur la carte
    SDL_Texture* TextureObstacle;
    bool choc; //Collision avec le joueur
    int compteurVitesse; //Compteur pour controler la vitesse de l'obstacle
};
/**
 * \brief Représentation des obstacles
*/
typedef struct obstacle obstacle_t;


void InitSpriteJoueur(SDL_Rect* DestR_JoueurSprite, SDL_Rect* SrcR_JoueurSprite);

int animationJoueur(int compteSprite, SDL_Rect* DestR_JoueurSprite, SDL_Rect* SrcR_JoueurSprite);

void init_joueur(joueur_t* joueur);

void initObstacle(obstacle_t* obstacle, int x, int y, int w, int h, int v);

void JumpJoueur(bool* jump, joueur_t* joueur, int* compteur, int* sens);

void handle_events(SDL_Event* evenements, bool* terminer, joueur_t* joueur);

void deplacementObstacle(obstacle_t* obstacle);

obstacle_t TrouverObstacle(char nomObstacle[]);