#include "./render.h"

/* Tiles */
pioTexture_t emptyTexture;
pioTexture_t dirtTexture;
pioTexture_t rockTexture;
pioTexture_t diamondTexture;
pioTexture_t doorTexture;
pioTexture_t waterTexture;
pioTexture_t borderTexture;

/* Entities */
pioTexture_t playerTexture;
pioTexture_t spiderTexture;
pioTexture_t monsterTexture;

/* Ui */
pioTexture_t timeTexture;
pioTexture_t saveTexture;

// If successfull, return 0
// Else, return 1
int loadTexture(pioTexture_t *pioTexture, char *path, SDL_Renderer *renderer)
{
    int status = 0;
    *pioTexture = loadPioTexture(path, renderer);
    resizePioTexture(pioTexture, TILE_WIDTH, TILE_HEIGHT);
    if(pioTexture->texture == NULL) {
        printf("Failed to load %s\n", path);
        status = 1;

    }

    return status;
}

// If successfull, return 1
// Else, return 0
int loadMedia(SDL_Renderer *renderer)
{
    int success = 1;

    /* Tiles */
    success += loadTexture(&emptyTexture, "./assets/emptyTexture.png", renderer);
    success += loadTexture(&dirtTexture, "./assets/dirtTexture.png", renderer);
    success += loadTexture(&rockTexture, "./assets/rockTexture.png", renderer);
    success += loadTexture(&diamondTexture, "./assets/diamondTexture.png", renderer);
    success += loadTexture(&doorTexture, "./assets/doorTexture.png", renderer);
    success += loadTexture(&waterTexture, "./assets/waterTexture.png", renderer);
    success += loadTexture(&borderTexture, "./assets/borderTexture.png", renderer);

    /* Entities */
    success += loadTexture(&playerTexture, "./assets/playerTexture.png", renderer);
    success += loadTexture(&spiderTexture, "./assets/spiderTexture.png", renderer);
    success += loadTexture(&monsterTexture, "./assets/monsterTexture.png", renderer);

    /* Ui */
    success += loadTexture(&timeTexture, "./assets/timeTexture.png", renderer);
    success += loadTexture(&saveTexture, "./assets/saveTexture.png", renderer);

    if(success == 1) return 1;
    else return 0;
}

// Free all of the loaded media
void closeMedia()
{
    destroyPioTexture(&emptyTexture);
    destroyPioTexture(&dirtTexture);
    destroyPioTexture(&rockTexture);
    destroyPioTexture(&diamondTexture);
    destroyPioTexture(&doorTexture);
    destroyPioTexture(&waterTexture);
    destroyPioTexture(&borderTexture);

    destroyPioTexture(&playerTexture);
    destroyPioTexture(&spiderTexture);
    destroyPioTexture(&monsterTexture);

    destroyPioTexture(&timeTexture);
    destroyPioTexture(&saveTexture);
}

// Render a frame
void renderFrame(SDL_Renderer *renderer) {
    SDL_RenderClear(renderer);
    renderPioTexture(waterTexture, 0, 0, renderer);
    SDL_RenderPresent(renderer);
}
