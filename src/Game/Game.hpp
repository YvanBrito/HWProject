#pragma once
#include<vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include "../Scene/Scene.hpp"

class Game {
private:
    const double MS_PER_UPDATE = 16.67;

    Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event e;
    int currentSceneIndex{ 0 };

    std::vector<Scene*> scenes;
    bool isCleanedUp;
    
public:

    static Game& getInstance();
    bool init();
    void run();
    void cleanup();

    ~Game();

    static Game *singleton;
    Scene* currentScene;

    static int kScreenWidth;
    static int kScreenHeight;
};
