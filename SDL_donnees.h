#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>

#include <math.h>

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
    bool peutMarcherSur; //Est-ce que le joueur peut sauter dessus ? (true pour "escaliers")
};
/**
 * \brief Représentation des obstacles
*/
typedef struct obstacle obstacle_t;


struct niveau{
    int numero;
    int nbObstacle; //nombre d'obstacle du niveau
    obstacle_t* tabObstacle;
};

typedef struct niveau niveau_t;

struct monde{
    SDL_Window* fenetre; //fenetre du jeu
    SDL_Event evenements; // Événements liés à la fenêtre
    SDL_Renderer* ecran; //rendu de l'écran
    SDL_Texture* fond; //fond du jeu
    SDL_Texture* menu; //menu principale du jeu
    SDL_Texture* curseur; //curseur du menu
    joueur_t joueur; //le joueur 
    niveau_t niveau; //niveau actuel
    bool fin;
    bool pause;
    int choix; //choix du joueur dans le menu
};

typedef struct monde monde_t;


void InitSpriteJoueur(SDL_Rect* DestR_JoueurSprite, SDL_Rect* SrcR_JoueurSprite);

int animationJoueur(int compteSprite, SDL_Rect* DestR_JoueurSprite, SDL_Rect* SrcR_JoueurSprite);

void init_joueur(joueur_t* joueur);

void initObstacle(obstacle_t* obstacle, int x, int y, int w, int h, int v, bool marchersur);

void JumpJoueur(bool* jump, joueur_t* joueur, int* compteur, int* sens);

void handle_events(SDL_Event* evenements, bool* terminer, joueur_t* joueur, bool* pause, int* choix);

void deplacementObstacle(obstacle_t* obstacle);

obstacle_t TrouverObstacle(char nomObstacle[], int posX);

bool sprites_collide(SDL_Rect sp2[1], SDL_Rect sp1[1]);