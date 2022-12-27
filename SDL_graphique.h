#include "SDL_donnees.h"

SDL_Window* SDL_CreateWindow(const char* title,
int x,
int y,
int w,
int h,
Uint32 flags);

SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer* renderer);

SDL_Texture* charger_image_transparente(const char* nomfichier, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);

obstacle_t* chargerniveau(int niveau, SDL_Renderer* ecran, int* nbObstacle);

void initTexture(monde_t* monde);