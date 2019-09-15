#include "./render.h"

TTF_Font *gFont = NULL;

pioTexture_t *tilableArray[ARR_SIZE];

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

void initTilableArray()
{
    tilableArray[1] = &emptyTexture;
    tilableArray[0] = &dirtTexture;
    tilableArray[2] = &rockTexture;
    tilableArray[3] = &diamondTexture;
    tilableArray[4] = &doorTexture;
    tilableArray[5] = &waterTexture;
    tilableArray[6] = &borderTexture;
    tilableArray[7] = &playerTexture;
    tilableArray[8] = &spiderTexture;
    tilableArray[9] = &monsterTexture;
}

// If successfull, return 0
// Else, return 1
int loadTexture(pioTexture_t *pioTexture, char *path, SDL_Renderer *renderer)
{
    int status = 0;
    *pioTexture = loadPioTexture(path, renderer);
    resizePioTexture(pioTexture, TILE_WIDTH, TILE_HEIGHT);
    if (pioTexture->texture == NULL)
    {
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
    SDL_Color textColor = {255, 255, 255};
    //*textFont = loadPioTextFont(path, renderer);
    *textFont = loadPioTextFont("init", textColor, font, renderer);
    resizePioTexture(&(textFont->texture), FONT_WIDTH, FONT_HEIGHT);
    if (textFont->texture.texture == NULL)
    {
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
    if (gFont == NULL)
    {
        printf("Failed to load zig font! SDL_ttf Error: %s\n", TTF_GetError());
        success += 1;
    }
    else
    {
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

    initTilableArray();

    if (success == 1)
        return 1;
    else
        return 0;
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

// Render palette of tiles
void renderPalette(pioWindow_t window, SDL_Renderer *renderer)
{
    int currX = 0;
    int currY = window.height - TILE_HEIGHT;
    for (int i = 0; i < ARR_SIZE; i++)
    {
        renderPioTexture(*tilableArray[i], currX + (i * TILE_WIDTH), currY, renderer);
    }
    renderPioTexture(saveTexture, window.width - TILE_WIDTH, currY, renderer);
}

// Render output grid
void renderGrid(pioWindow_t window, SDL_Renderer *renderer, output_t o, camera_t cam)
{
    for (int y = 0, row = cam.row; y < window.height - TILE_HEIGHT; y += TILE_HEIGHT, row++)
    {
        for (int x = 0, col = cam.col; x < window.width; x += TILE_WIDTH, col++)
        {
            if (row < o.row && row >= 0 && col < o.col && col >= 0)
            { // is inside array
                switch (o.arr[row][col])
                {
                case emptyTile:
                    renderPioTexture(emptyTexture, x, y, renderer);
                    break;
                case dirtTile:
                    renderPioTexture(dirtTexture, x, y, renderer);
                    break;
                case borderTile:
                    renderPioTexture(borderTexture, x, y, renderer);
                    break;
                }
            }
        }
    }
}

// Render a frame
void renderFrame(pioWindow_t window, SDL_Renderer *renderer, output_t o, camera_t cam)
{
    SDL_RenderClear(renderer);
    renderGrid(window, renderer, o, cam);
    renderPalette(window, renderer);
    SDL_RenderPresent(renderer);
}
