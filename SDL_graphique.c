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
