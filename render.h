#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "./wrappers/pio-texture.h"
#include "./wrappers/pio-text-font.h"
#include "./wrappers/pio-window.h"

#define TILE_WIDTH 64
#define TILE_HEIGHT 64
#define FONT_WIDTH 32
#define FONT_HEIGHT 32

void renderFrame(SDL_Renderer *renderer);
void renderInputScene(SDL_Renderer *renderer, char *name, int time, int diamond);

int loadMedia(SDL_Renderer *renderer);

void closeMedia();

#endif