#include "Game.hpp"

int Game::kScreenWidth = 1920;
int Game::kScreenHeight = 1080;

Game::Game() {
    this->window = nullptr;
    this->renderer = nullptr;
    this->currentScene = nullptr;
    this->isCleanedUp = false;
    this->scenes.push_back(new Scene());
    this->currentScene = this->scenes[currentSceneIndex];
    SDL_zero(e);
}

Game& Game::getInstance() {
    static Game instance;
    return instance;
}

bool Game::init() {
    bool success{ true };

    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        SDL_Log( "SDL could not initialize! SDL error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        window = SDL_CreateWindow( "HWProject", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                    kScreenWidth, kScreenHeight, SDL_WINDOW_SHOWN );
        if( window == nullptr )
        {
            SDL_Log( "Window could not be created! SDL error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
            if( renderer == nullptr )
            {
                SDL_Log( "Renderer could not be created! SDL error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
                else
                {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                    if( this->currentScene->init(renderer) == false )
                    {
                        SDL_Log( "Failed to initialize scene!\n" );
                        success = false;
                    }
                }
            }
        }
    }

    return success;
}

void Game::run() {
    bool quit{ false };
    Uint32 previousTime = SDL_GetTicks();
    double lag = 0.0;

    while( quit == false )
    {
        Uint32 currentTime = SDL_GetTicks();
        double elapsedTime = currentTime - previousTime;
        previousTime = currentTime;
        lag += elapsedTime;

        while( SDL_PollEvent( &this->e ) != 0 )
        {
            if( this->e.type == SDL_QUIT )
            {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN)
            {
                if( e.key.keysym.sym == SDLK_ESCAPE )
                {
                    quit = true;
                }
            }
            
            this->currentScene->processInput( this->e );
        }

        while (lag >= MS_PER_UPDATE) {
            this->currentScene->update();
            lag -= MS_PER_UPDATE;
        }
        
        this->currentScene->render(renderer);
    } 
}

void Game::cleanup() {
    if (isCleanedUp) {
        return;
    }
    
    isCleanedUp = true;
    
    currentScene = nullptr;
    
    for(Scene* scene : scenes) {
        if (scene != nullptr) {
            delete scene;
        }
    }
    scenes.clear();
    
    if (renderer != nullptr) {
        SDL_DestroyRenderer( renderer );
        renderer = nullptr;
    }
    if (window != nullptr) {
        SDL_DestroyWindow( window );
        window = nullptr;
    }
    
    Mix_Quit();
    SDL_Quit();
}

Game::~Game() {
    cleanup();
}