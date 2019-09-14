#include "./pio-window.h"

pioWindow_t createPioWindow(SDL_Window *window, int width, int height) {
    pioWindow_t rtr;
    rtr.window = window;
    rtr.width = width;
    rtr.height = height;
    return rtr;
}

void destroyPioWindow(pioWindow_t *pioWindow) {
    SDL_DestroyWindow(pioWindow->window);
    pioWindow->window = NULL;
}

void updateWindowDims(pioWindow_t *pioWindow) {
    int newWidth, newHeight;
    SDL_GetWindowSize(pioWindow->window, &newWidth, &newHeight);
    pioWindow->width = newWidth;
    pioWindow->height = newHeight;
}