#ifndef PIO_WINDOW_H
#define PIO_WINDOW_H

#include <SDL2/SDL.h>

typedef struct PioWindow {
    SDL_Window *window;
    int width, height;
} pioWindow_t;

pioWindow_t createPioWindow (SDL_Window *window, int w, int h);

void destroyPioWindow(pioWindow_t *pioWindow);

void updateWindowDims(pioWindow_t *pioWindow); 

#endif