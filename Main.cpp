#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
#include "Globals.h"
#include "PikoTexture.h"
#include "pikoGameObject.h"
#include <math.h>

SDL_Window* window;
SDL_Renderer* renderer;

// Set the desired FPS
const int roomSpeed = 60;
const int frameDelay = 1000 / roomSpeed; // ms per frame

void pikoRect(int x, int y, int width, int height)
{
    // Render red filled quad
    SDL_Rect fillRect = {x, y, width, height};
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &fillRect);
}

float degToRed(float degree)
{
    return degree * (M_PI / 180);
}

// A specific game object, e.g., a player or enemy
class Player : public GameObject {
public:

    int position = 0;

    virtual void step()
    {
        x = 50;
        y = 50;


        if (position > 360)
            position = 0;

        x += std::cos(position) * 30;
        y += std::sin(position) * 30;

        position++;
    }

    virtual void draw(double deltaTime)
    {

        pikoRect(x, y, 32, 32);

    };

    // Implementing the update method for the player
    void update(double deltaTime) override 
    {
        



        

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

    Uint32 frameStart;
    int frameTime;

    // While application is running
    while (!quit) {

        frameStart = SDL_GetTicks();

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
            obj->draw(0);
            obj->step();
        }


        // Calculate the time taken to process and render the frame
        frameTime = SDL_GetTicks() - frameStart;

        // If the frame is processed quicker than the frame time, delay the loop
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
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