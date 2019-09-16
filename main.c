#include "./libs/include/SDL.h"
#include "./libs/include/SDL_image.h"
#include "./libs/include/SDL_ttf.h"

#include <string.h>

#include "./render.h"
#include "./wrappers/pio-window.h"
#include "./output.h"
#include "./camera.h"

#define INIT_WIDTH 1366
#define INIT_HEIGHT 720

const char *TITLE = "pioEditor";

output_t gOutput;
camera_t gCamera;

pioWindow_t gWindow;
SDL_Renderer *gRenderer = NULL;

// If successfull, return 1
// Else, return 0
int init()
{
    int success = 1;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = 0;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!\n");
        }

        SDL_Window *tmpWindow = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, INIT_WIDTH, INIT_HEIGHT, SDL_WINDOW_RESIZABLE);
        if (tmpWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = 0;
        }
        else
        {
            gWindow.window = tmpWindow;
            updateWindowDims(&gWindow);
            gRenderer = SDL_CreateRenderer(gWindow.window, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = 0;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);

                //Initialize image loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = 0;
                }

                //Initialize font loading
                if (TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    success = 0;
                }
            }
        }
    }

    return success;
}

// Free everything
void closeAll()
{
    closeMedia();
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    destroyPioWindow(&gWindow);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

int main(int argc, char *args[])
{
    int successArguments = 0;
    if (argc != 6)
    {
        printf("You need to pass 5 arguments: \n");
        printf("Name, time, diaReq, row, col\n");
    }
    else
    {
        gOutput.name = (char *)malloc(100 * sizeof(char));
        strcpy(gOutput.name, args[1]);
        char *timeStr = args[2];
        char *diaReqStr = args[3];
        char *rowStr = args[4];
        char *colStr = args[5];
        gOutput.time = atoi(timeStr);
        gOutput.diaReq = atoi(diaReqStr);
        gOutput.row = atoi(rowStr);
        gOutput.col = atoi(colStr);
        debugOutput(gOutput);
        initArray(&gOutput);
        //debugArray(gOutput);
        successArguments = 1;
    }

    gCamera = createCamera();

    if (!init() || successArguments == 0)
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        if (!loadMedia(gRenderer))
        {
            printf("Failed to load media!\n");
        }
        else
        {
            int quit = 0;

            char selectedTile = dirtTile;

            SDL_Event e;

            renderFrame(gWindow, gRenderer, gOutput, gCamera);

            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = 1;
                    }
                    else if (e.type == SDL_KEYDOWN)
                    {
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_UP:
                            updateCamera(&gCamera, gCamera.row - 1, gCamera.col);
                            break;
                        case SDLK_DOWN:
                            updateCamera(&gCamera, gCamera.row + 1, gCamera.col);
                            break;
                        case SDLK_LEFT:
                            updateCamera(&gCamera, gCamera.row, gCamera.col - 1);
                            break;
                        case SDLK_RIGHT:
                            updateCamera(&gCamera, gCamera.row, gCamera.col + 1);
                            break;
                        default:
                            break;
                        }
                    }
                    else if (e.type == SDL_WINDOWEVENT)
                    {
                        switch (e.window.event)
                        {
                        case SDL_WINDOWEVENT_RESIZED:
                            updateWindowDims(&gWindow);

                            break;

                        default:
                            break;
                        }
                    }
                    else if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        if (e.button.button == SDL_BUTTON_LEFT)
                        {
                            int mousePosX, mousePosY;
                            int tileX, tileY;
                            SDL_GetMouseState(&mousePosX, &mousePosY);
                            tileX = mousePosX / TILE_WIDTH;
                            tileY = mousePosY / TILE_HEIGHT;
                            tileX += gCamera.col; //col
                            tileY += gCamera.row; //row
                            //printf("%d,%d, CAM %d,%d POS %d,%d\n", tileY, tileX, gCamera.row, gCamera.col, mousePosX, mousePosY);
                            if (mousePosY / TILE_HEIGHT >= (gWindow.height / TILE_HEIGHT) - 1)
                            {
                                int selTilePosX = mousePosX / TILE_WIDTH;
                                printf("%d\n", selTilePosX);
                                switch (selTilePosX)
                                {
                                case 0:
                                    selectedTile = dirtTile;
                                    break;
                                case 1:
                                    selectedTile = emptyTile;
                                    break;
                                case 2:
                                    selectedTile = rockTile;
                                    break;
                                case 3:
                                    selectedTile = diamondTile;
                                    break;
                                case 4:
                                    selectedTile = doorTile;
                                    break;
                                case 5:
                                    selectedTile = waterTile;
                                    break;
                                case 6:
                                    selectedTile = borderTile;
                                    break;
                                case 7:
                                    selectedTile = playerTile;
                                    break;
                                case 8:
                                    selectedTile = spiderTile;
                                    break;
                                case 9:
                                    selectedTile = monsterTile;
                                    break;
                                }
                            }
                            else if (tileX < gOutput.col && tileX >= 0 && tileY >= 0 && tileY < gOutput.row)
                            {
                                gOutput.arr[tileY][tileX] = selectedTile;
                                //debugArray(gOutput);
                            }
                        } else if(e.button.button == SDL_BUTTON_RIGHT) {
                            int mousePosX, mousePosY;
                            int tileX, tileY;
                            SDL_GetMouseState(&mousePosX, &mousePosY);
                            tileX = mousePosX / TILE_WIDTH;
                            tileY = mousePosY / TILE_HEIGHT;
                            tileX += gCamera.col; //col
                            tileY += gCamera.row; //row
                            if (tileX < gOutput.col && tileX >= 0 && tileY >= 0 && tileY < gOutput.row)
                            {
                                printf("del\n");
                                gOutput.arr[tileY][tileX] = emptyTile;
                                //debugArray(gOutput);
                            }
                        }
                    }
                    renderFrame(gWindow, gRenderer, gOutput, gCamera);
                }
            }
        }
    }

    exportOutput(gOutput, "./plswork.txt");
    closeAll();

    return 0;
}