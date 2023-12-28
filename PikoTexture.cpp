#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
#include "Globals.h"
#include "PikoTexture.h"



    SDL_Texture* pikoTexture::pikoLoadTexture(const char* file)
    {
        // Load image into surface
        SDL_Surface* surface = IMG_Load(file);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        // Free the surface immediately if you don't need it anymore
        SDL_FreeSurface(surface);    // Load image into surface

        return texture;
    }

    void pikoTexture::pikoSetTextureRect(int x, int y, int width, int height, pikoTextureRect option)
    {
        if (option == PIKO_SOURCE_RECT)
            srcRect = { x, y, width, height };
        else if (option == PIKO_DESTINATION_RECT)
            destRect = { x, y, width, height };
    }

    void pikoTexture::pikoRenderTexture()
    {
        // Render texture to screen
        SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
    }

    pikoTexture::pikoTexture(const char* file)
    {
        texture = pikoLoadTexture(file);
        printf("texture created");
    }

    pikoTexture::~pikoTexture()
    {
        SDL_DestroyTexture(texture);
        printf("texture destroyed");
    }

