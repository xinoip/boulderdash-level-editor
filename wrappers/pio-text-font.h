#ifndef PIO_TEXT_FONT_H
#define PIO_TEXT_FONT_H

#include <stdio.h>
#include <string.h>
#include "../libs/include/SDL_ttf.h"
#include "./pio-texture.h"

typedef struct PioTextFont {
    char *text;
    SDL_Color color;
    TTF_Font *font;
    pioTexture_t texture;
} pioTextFont_t;

//Creates PioTextFont with given properties and renderer
pioTextFont_t loadPioTextFont(char *text, SDL_Color color, TTF_Font *font, SDL_Renderer *renderer);

//Changes the text value of given PioTextFont with the given renderer
void updatePioTextFont(pioTextFont_t *currObj, char *newText, SDL_Renderer *renderer);

//Frees given PioTextFont from memory
void destroyPioTextFont(pioTextFont_t text);

/*
    For rendering PioTextFont use renderPioTexture with the pioTexture_t propertie of font
 */

#endif