#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>

#include <math.h>

#define CompteurSpriteJoueur 200

#define CompteurJump 5
#define CompteurObstacle 3
#define CompteurFinNiveau 4000

#define PosXJoueur 100
#define PosYJoueur 399

#define HauteurSol 255

#define HauteurEcran 720
#define LargeurEcran 1280

#define JoueurW 200/3
#define JoueurH 400/6
#define JoueurHenRoulade 40

#define LimiteYJump 300 //Limite de la hauteur du saut, une fois atteinte, le joueur commence à redescendre

#define PosPremierObstacleNiveau 1200 //Coordonnée x du premier obstacle des niveaux

struct joueur{
    SDL_Rect SpriteGraphique[1]; //Position du joueur sur la carte
    SDL_Rect SpriteFichier[1]; //Position du sprite du joueur dans le fichier
    SDL_Texture* JoueurSprite; //Texture du joueur
    int compteurSprite; //Compteur pour contrôler la vitesse de défilement des images du sprite
    int sensJump; // Sens du saut (d'abord monter puis descendre);
    int compteurJump; //Compteur pour contrôler la vitesse du saut
    bool jump; //Est-ce que le joueur saute ?
    bool roulade; //Est-ce que le joueur fait une roulade ?
    bool animation; //Activer/désactiver l'animation du joueur
    bool CoupDePied; //Quand il appuie sur la touche du coup de pied 
};

typedef struct joueur joueur_t;

struct obstacle{
    SDL_Rect SpriteGraphique[1]; //Position du sprite sur la carte
    SDL_Texture* TextureObstacle; //texture de l'obstacle
    bool choc; //Collision avec le joueur
    int compteurVitesse; //Compteur pour controler la vitesse de l'obstacle
    bool peutEtrecasse; //Est-ce que le joueur peut le casser ? (Pour coups de pieds)
    bool estDetruit; //Si il peut être cassé et il se casse, alors true
};
/**
 * \brief Représentation des obstacles
*/
typedef struct obstacle obstacle_t;


struct niveau{
    int numero; //numéro du niveau
    int nbObstacle; //nombre d'obstacle du niveau
    obstacle_t* tabObstacle; //tableau contenant tout les obstacles du niveau
    int compteurFin; //compteur avant que le niveau ne se termine une fois que le joueur a passé le dernier obstacle
    SDL_Texture* victoire; //écriture "victoire" à la fin du niveau
};

typedef struct niveau niveau_t;


struct souris{
    int posX; //Position x de la souris
    int posY; //Position y de la souris
};

typedef struct souris souris_t;

struct menu{
    SDL_Texture* texturemenu; //l'image affiché pour le menu
    SDL_Texture* curseur; //image représentant le curseur
    int choix; //choix actuel du joueur (un choix = une case séléctionnée)
    SDL_Rect placecurseur[1]; //place du curseur à l'écran, qui bouge selon le choix du joueur
    souris_t souris;
};

typedef struct menu menu_t;

struct monde{
    SDL_Window* fenetre; //fenetre du jeu
    SDL_Event evenements; // Événements liés à la fenêtre
    SDL_Renderer* ecran; //rendu de l'écran
    SDL_Texture* fond; //fond du jeu
    joueur_t joueur; //le joueur 
    niveau_t niveau; //niveau actuel
    menu_t menu; //le menu
    bool fin; //fin du jeu ?
    bool pause; //jeux en pause ?
    int niveauAccompli; //nombre de niveau accompli (de 0 à 3)
};

typedef struct monde monde_t;


void InitSpriteJoueur(SDL_Rect* DestR_JoueurSprite, SDL_Rect* SrcR_JoueurSprite);

int animationJoueur(int compteSprite, SDL_Rect* DestR_JoueurSprite, SDL_Rect* SrcR_JoueurSprite);

void init_joueur(joueur_t* joueur);

void initObstacle(obstacle_t* obstacle, int x, int y, int w, int h, int v, bool peutCasser);

void JumpJoueur(bool* jump, joueur_t* joueur, int* compteur, int* sens);

void handle_events(SDL_Event* evenements, bool* terminer, joueur_t* joueur, bool* pause, int* choix, niveau_t* niveau, SDL_Renderer* ecran, bool* roulade, souris_t* souris, int* niveauAccompli);

void deplacementObstacle(obstacle_t* obstacle);

obstacle_t TrouverObstacle(char nomObstacle[], int posX);

bool sprites_collide(SDL_Rect sp1[1], SDL_Rect sp2[1], int bonusRoulade);

void handle_pause(joueur_t* joueur, menu_t* menu, SDL_Renderer* ecran);

void handle_choix(int* choix, niveau_t* niveau, SDL_Renderer* ecran, bool* terminer, bool* pause, int* niveauAccompli);

void victoire(niveau_t* niveau, bool* pause, SDL_Renderer* ecran, int* niveauAccompli);

void initMonde(monde_t* monde);