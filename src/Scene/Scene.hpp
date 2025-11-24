#pragma once

#include<vector>
#include<SDL2/SDL.h>
#include<SDL2/SDL_main.h>
#include "../GameObject/GameObject.hpp"

class Scene {
public:
    Scene();
    bool init(SDL_Renderer* renderer);
    void processInput(SDL_Event& e);
    void update();
    void render(SDL_Renderer* renderer);
    void instantiate(GameObject* gameObject);
    void queueInstantiate(GameObject* gameObject);
    ~Scene();
private:
    std::vector<GameObject*> gameObjects;
    std::vector<GameObject*> pendingObjects;
    SDL_Renderer* gRenderer;
    
    void processPendingObjects();
};