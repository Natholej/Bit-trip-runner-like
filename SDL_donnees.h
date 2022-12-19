#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>

#define CompteurSpriteJoueur 200

#define CompteurJump 5

#define PosXJoueur 50
#define PosYJoueur 300

struct joueur{
    SDL_Rect SpriteGraphique[1];
    SDL_Rect SpriteFichier[1];
    SDL_Texture* JoueurSprite;
    int compteurSprite;
    int sensJump;
    int compteurJump;
    bool jump;
    bool animation;
};

typedef struct joueur joueur_t;


void InitSpriteJoueur(SDL_Rect* DestR_JoueurSprite, SDL_Rect* SrcR_JoueurSprite);

int animationJoueur(int compteSprite, SDL_Rect* DestR_JoueurSprite, SDL_Rect* SrcR_JoueurSprite);

void init_joueur(joueur_t* joueur);

void JumpJoueur(bool* jump, joueur_t* joueur, int* compteur, int* sens);

void handle_events(SDL_Event* evenements, bool* terminer, joueur_t* joueur);