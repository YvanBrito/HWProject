#pragma once
#include <SDL.h>
#include "Texture/Texture.hpp"
#include "Vector2/Vector2.hpp"

class Scene;

class GameObject {
protected:
    Texture *texture;
    Vector2 *position;
    Vector2 *velocity;
    Scene* scene;
    
public:
    GameObject();
    
    void setScene(Scene* scene) { this->scene = scene; }
    Scene* getScene() const { return scene; }
    
    virtual void init(SDL_Renderer* renderer) = 0;
    virtual void processInput(SDL_Event& e) {}
    virtual void update() = 0;
    virtual void render() = 0;
    virtual ~GameObject();
};