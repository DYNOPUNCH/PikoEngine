#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>

SDL_Renderer* renderer;

void pikoRect(int x, int y, int width, int height)
{
    // Render red filled quad
    SDL_Rect fillRect = {x, y, width, height};
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &fillRect);
}

SDL_Texture* pikoLoadTexture(const char* file)
{
    // Load image into surface
    SDL_Surface* surface = IMG_Load(file);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Free the surface immediately if you don't need it anymore
    SDL_FreeSurface(surface);    // Load image into surface

    return texture;
}

struct pikoTexture
{

    private:

        SDL_Texture* texture = NULL;
        SDL_Rect srcRect = {0, 0, 0, 0};
        SDL_Rect destRect = {0, 0, 0, 0};

    public:
        
        enum pikoTextureRect
        {
            PIKO_SOURCE_RECT,
            PIKO_DESTINATION_RECT
        };

        void pikoSetTextureRect(int x, int y, int width, int height, pikoTextureRect option)
        {
            if(option == PIKO_SOURCE_RECT)
                srcRect = {x, y, width, height};
            else if(option == PIKO_DESTINATION_RECT)
                destRect = { x, y, width, height };
        }

        void pikoRenderTexture()
        {
            // Render texture to screen
            SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
        }

        pikoTexture(const char *file)
        {
            texture = pikoLoadTexture(file);
            printf("texture created");
        }

        ~pikoTexture()
        {
            SDL_DestroyTexture(texture);
            printf("texture destroyed");
        }
};



// Base class for all game objects
class GameObject {
public:

    int x = 0;
    int y = 0;

    // The update method, which should be overridden by derived classes
    virtual void update(double deltaTime) = 0;
};

// A specific game object, e.g., a player or enemy
class Player : public GameObject {
public:
    // Implementing the update method for the player
    void update(double deltaTime) override {
        pikoRect(x, y, 400, 400);
    }
};


void pikoRenderTexture(SDL_Texture* texture, int x, int y, int width, int height, int clipX, int clipY, int clipWidth, int clipHeight)
{
    SDL_Rect srcRect = {clipX, clipY, clipWidth, clipHeight};
    SDL_Rect destRect = { x, y, width, height };

    // Render texture to screen
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}

int main(int argc, char* args[])
{
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("Man", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Main loop flag
    int quit = 0;

    // Event handler
    SDL_Event e;

    pikoTexture* pik = new pikoTexture("400.jpg");
    pik->pikoSetTextureRect(0, 0, 300, 300, pikoTexture::PIKO_SOURCE_RECT);
    pik->pikoSetTextureRect(0, 0, 300, 300, pikoTexture::PIKO_DESTINATION_RECT);

    std::vector<GameObject*> gameObjects;

    Player* player = new Player();
    gameObjects.push_back(player);

    // While application is running
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // Update each game object
        for (auto obj : gameObjects) 
        {
            obj->update(0);
        }

        // Update screen
        SDL_RenderPresent(renderer);
    }

    delete pik;

    // Free resources and close SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}