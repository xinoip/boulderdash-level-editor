#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include "./wrappers/pio-texture.h"
#include "./wrappers/pio-window.h"

#define TILE_WIDTH 64
#define TILE_HEIGHT 64

void renderFrame(SDL_Renderer *renderer);

int loadMedia(SDL_Renderer *renderer);

void closeMedia();

#endif