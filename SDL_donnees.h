#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>

#define CompteurSpriteJoueur 200

#define PosXJoueur 50
#define PosYJoueur 300

struct joueur{
    SDL_Rect SpriteGraphique[1];
    SDL_Rect SpriteFichier[1];
    int compteurSprite;
    SDL_Texture* JoueurSprite;
};

typedef struct joueur joueur_t;


void InitSpriteJoueur(SDL_Rect* DestR_JoueurSprite, SDL_Rect* SrcR_JoueurSprite);

int animationJoueur(int compteSprite, SDL_Rect* DestR_JoueurSprite, SDL_Rect* SrcR_JoueurSprite);

void init_joueur(joueur_t* joueur);