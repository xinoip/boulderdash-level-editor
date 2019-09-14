#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "./render.h"
#include "./wrappers/pio-window.h"
#include "./controls.h"

#define INIT_WIDTH 1366
#define INIT_HEIGHT 720

const char *TITLE = "pioEditor";

typedef struct Output
{
    char *name;
    int time;
    int diaReq;
} output_t;

output_t gOutput;
void debugOutput() {
    printf("name: %s\n", gOutput.name);
    printf("time: %d\n", gOutput.time);
    printf("diaReq: %d\n", gOutput.diaReq);
}

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
    if(argc != 4) {
        printf("You need to pass 3 arguments: \n");
        printf("Name, time, diaReq\n");
    } else {
        gOutput.name = (char *)malloc(100*sizeof(char));
        strcpy(gOutput.name, args[1]);
        char *timeStr = args[2];
        char *diaReqStr = args[3];
        gOutput.time = atoi(timeStr);
        gOutput.diaReq = atoi(diaReqStr);
        debugOutput();
        successArguments = 1;
    }

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

            SDL_Event e;

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
                }

                renderFrame(gRenderer);
            }
        }
    }

    closeAll();

    return 0;
}