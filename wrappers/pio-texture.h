#ifndef PIO_TEXTURE_H
#define PIO_TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct PioTexture {
    int width, height;
    SDL_Texture *texture;
} pioTexture_t;

//Creates pioTexture with given path and renderer
pioTexture_t loadPioTexture(char *path, SDL_Renderer *renderer);

//Renders given texture at (x,y) using the given renderer
//(x,y) will be upper-left corner of the image
void renderPioTexture(pioTexture_t p, int x, int y, SDL_Renderer *renderer);

//Frees given pioTexture from memory
void destroyPioTexture(pioTexture_t *p); 

//Resizes given pioTexture with given newWidth and newHeight values
//Streches or minimizes the texture
void resizePioTexture(pioTexture_t *p, int newWidth, int newHeight); 

#endif