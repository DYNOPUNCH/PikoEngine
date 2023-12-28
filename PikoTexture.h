#ifndef PIKOTEXTURE
#define PIKOTEXTURE

class pikoTexture
{

private:

    SDL_Texture* texture = NULL;
    SDL_Rect srcRect = { 0, 0, 0, 0 };
    SDL_Rect destRect = { 0, 0, 0, 0 };

public:

    enum pikoTextureRect
    {
        PIKO_SOURCE_RECT,
        PIKO_DESTINATION_RECT
    };

    SDL_Texture* pikoLoadTexture(const char* file);

    void pikoSetTextureRect(int x, int y, int width, int height, pikoTextureRect option);

    void pikoRenderTexture();

    pikoTexture(const char* file);

    ~pikoTexture();
};

#endif