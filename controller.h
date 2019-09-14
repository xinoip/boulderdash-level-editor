#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SDL2/SDL.h>

typedef enum state
{
    naming,
    timing,
    reqDia
} state_t;

void handleInputScene(SDL_Event e);

#endif