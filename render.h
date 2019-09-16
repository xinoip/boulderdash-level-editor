#ifndef RENDER_H
#define RENDER_H

#include "./libs/include/SDL.h"
#include "./libs/include/SDL_ttf.h"
#include "./wrappers/pio-texture.h"
#include "./wrappers/pio-text-font.h"
#include "./wrappers/pio-window.h"
#include "./output.h"
#include "./camera.h"
#include "./base.h"

#define TILE_WIDTH 64
#define TILE_HEIGHT 64
#define FONT_WIDTH 32
#define FONT_HEIGHT 32
#define ARR_SIZE 10

void renderFrame(pioWindow_t window, SDL_Renderer *renderer, output_t o, camera_t cam);

int loadMedia(SDL_Renderer *renderer);

void closeMedia();

#endif