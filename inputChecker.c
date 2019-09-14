#include "./inputChecker.h"

int isDigit(SDL_Event e) {
    switch(e.key.keysym.sym) {
        case SDLK_1:
            printf("ITS HOTDOG\n");
        break;
        default:
        printf("NOT HOTDOG\n");
        break;
    }
    
    
    return 1;
}