#include "./pio-text-font.h"

pioTextFont_t loadPioTextFont(char *text, SDL_Color color, TTF_Font *font, SDL_Renderer *renderer) {

    pioTextFont_t rtr;
    rtr.text = malloc(sizeof(char) * 100);
    strcpy(rtr.text, text);
    rtr.color = color;
    rtr.font = font;

    SDL_Surface *textSurface = TTF_RenderText_Solid(rtr.font, rtr.text, rtr.color);
    if(textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());

    } else {
        rtr.texture.texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(rtr.texture.texture == NULL) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());

        } else {
            rtr.texture.width = textSurface->w;
            rtr.texture.height = textSurface->h;

        }

        SDL_FreeSurface(textSurface);
        textSurface = NULL;
    }

    return rtr;

}

void updatePioTextFont(pioTextFont_t *currObj, char *newText, SDL_Renderer *renderer) {

    strcpy(currObj->text, newText);
    destroyPioTexture(&(currObj->texture));

    SDL_Surface *textSurface = TTF_RenderText_Solid(currObj->font, currObj->text, currObj->color);
    if(textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());

    } else {
        currObj->texture.texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(currObj->texture.texture == NULL) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());

        } else {
            currObj->texture.width = textSurface->w;
            currObj->texture.height = textSurface->h;

        }

        SDL_FreeSurface(textSurface);
        textSurface = NULL;
    }

}

void destroyPioTextFont(pioTextFont_t text) {

    text.text = NULL;
    destroyPioTexture(&(text.texture));

}