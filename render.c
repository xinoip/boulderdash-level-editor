#include "./render.h"

TTF_Font *gFont = NULL;

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

/* Ui Textures */
pioTexture_t timeTexture;
pioTexture_t saveTexture;

/* Ui Texts */
pioTextFont_t mainText;

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

// If successfull, return 0
// Else, return 1
int loadFont(pioTextFont_t *textFont, TTF_Font *font, SDL_Renderer *renderer)
{
    int status = 0;
    SDL_Color textColor = {255,255,255};
    //*textFont = loadPioTextFont(path, renderer);
    *textFont = loadPioTextFont("init", textColor, font, renderer);
    resizePioTexture(&(textFont->texture), FONT_WIDTH, FONT_HEIGHT);
    if(textFont->texture.texture == NULL) {
        printf("Failed to load font!\n");
        status = 1;

    }

    return status;
}

// If successfull, return 1
// Else, return 0
int loadMedia(SDL_Renderer *renderer)
{
    int success = 1;

    gFont = TTF_OpenFont("./assets/zig.ttf", 28);
    if(gFont == NULL) {
        printf("Failed to load zig font! SDL_ttf Error: %s\n",TTF_GetError());
        success += 1;

    } else {
        /* Fonts */
        success += loadFont(&mainText, gFont, renderer);

    }

    

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
    destroyPioTextFont(mainText);

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
    renderInputScene(renderer, "asd_", 2, 5);
    SDL_RenderPresent(renderer);
}

void renderInputScene(SDL_Renderer *renderer, char *name, int time, int diamond) {
    /* Positions */
    int labelX = 300;
    int labelY = 300;
    int valueX = labelX + 632;
    int valueY = labelY;

    /* Integers to String */
    char timeText[12];
    char diaText[12];
    sprintf(timeText, "%d", time);
    sprintf(diaText, "%d", diamond);

    /* Labels */
    updatePioTextFont(&mainText, "Level Name:", renderer);
    renderPioTexture(mainText.texture, labelX, labelY, renderer);
    updatePioTextFont(&mainText, "Level Time:", renderer);
    renderPioTexture(mainText.texture, labelX, labelY + 64, renderer);
    updatePioTextFont(&mainText, "Req. Diamonds:", renderer);
    renderPioTexture(mainText.texture, labelX, labelY + 128, renderer);

    /* Values */
    updatePioTextFont(&mainText, name, renderer);
    renderPioTexture(mainText.texture, valueX, valueY, renderer);
    updatePioTextFont(&mainText, timeText, renderer);
    renderPioTexture(mainText.texture, valueX, valueY + 64, renderer);
    updatePioTextFont(&mainText, diaText, renderer);
    renderPioTexture(mainText.texture, valueX, valueY + 128, renderer);
}