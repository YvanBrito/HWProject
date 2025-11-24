#pragma once
#include <SDL.h>
#include <SDL2/SDL_mixer.h>
#include "Texture/Texture.hpp"
#include "Vector2/Vector2.hpp"
#include "../GameObject/GameObject.hpp"

class Player: public GameObject {
public:
    Player();

    void init(SDL_Renderer* renderer) override;
    void processInput(SDL_Event& e) override;
    void update() override;
    void render() override;
    Vector2 getPosition();

    ~Player();
private:
    Texture *texture;
    Vector2 *velocity;
    Vector2 *position;
    Mix_Chunk* gShot = nullptr;
};
