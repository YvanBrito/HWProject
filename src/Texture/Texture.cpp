#include "Texture.hpp"

Texture::Texture(SDL_Renderer* renderer):
    mTexture{ nullptr },
    mWidth{ 0 },
    mHeight{ 0 },
    gRenderer{ renderer }
{

}

Texture::~Texture()
{
    destroy();
}

bool Texture::loadFromFile( std::string path )
{
    destroy();

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == nullptr )
    {
        SDL_Log( "Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
        if( SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0x00, 0xFF, 0xFF ) ) < 0 )
        {
            SDL_Log( "Unable to color key! SDL error: %s", SDL_GetError() );
        }
        else
        {
            mTexture = SDL_CreateTextureFromSurface( this->gRenderer, loadedSurface );
            if( mTexture == nullptr )
            {
                SDL_Log( "Unable to create texture from loaded pixels! SDL error: %s\n", SDL_GetError() );
            }
            else
            {
                mWidth = loadedSurface->w;
                mHeight = loadedSurface->h;
            }
        }
        
        SDL_FreeSurface( loadedSurface );
    }

    return mTexture != nullptr;
}

void Texture::destroy()
{
    SDL_DestroyTexture( mTexture );
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

void Texture::render( float x, float y, SDL_FRect* clip, float width, float height )
{
    SDL_Rect dstRect{ static_cast<int>(x), static_cast<int>(y), mWidth, mHeight };

    if( clip != nullptr )
    {
        dstRect.w = static_cast<int>(clip->w);
        dstRect.h = static_cast<int>(clip->h);
    }

    if( width > 0 )
    {
        dstRect.w = static_cast<int>(width);
    }
    if( height > 0 )
    {
        dstRect.h = static_cast<int>(height);
    }

    SDL_Rect srcRect;
    if( clip != nullptr )
    {
        srcRect.x = static_cast<int>(clip->x);
        srcRect.y = static_cast<int>(clip->y);
        srcRect.w = static_cast<int>(clip->w);
        srcRect.h = static_cast<int>(clip->h);
        SDL_RenderCopy( gRenderer, mTexture, &srcRect, &dstRect );
    }
    else
    {
        SDL_RenderCopy( gRenderer, mTexture, nullptr, &dstRect );
    }
}

int Texture::getWidth()
{
    return mWidth;
}

int Texture::getHeight()
{
    return mHeight;
}

bool Texture::isLoaded()
{
    return mTexture != nullptr;
}