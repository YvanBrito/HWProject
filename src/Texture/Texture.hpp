#pragma once
#include <string>
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>

class Texture
{
public:
    static constexpr float kOriginalSize = -1.f;

    Texture(SDL_Renderer* renderer);

    ~Texture();

    bool loadFromFile( std::string path );

    void destroy();

    void render( float x, float y, SDL_FRect* clip = nullptr, float width = kOriginalSize, float height = kOriginalSize );

    int getWidth();
    int getHeight();
    bool isLoaded();

private:
    SDL_Texture* mTexture;
    SDL_Renderer* gRenderer;
    
    int mWidth;
    int mHeight;
};