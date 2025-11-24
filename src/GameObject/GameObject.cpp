#include "GameObject.hpp"

GameObject::GameObject() {
    this->texture = nullptr;
    this->position = nullptr;
    this->velocity = nullptr;
    this->scene = nullptr;
}

GameObject::~GameObject() {
    delete this->texture;
    this->texture = nullptr;
    delete this->position;
    this->position = nullptr;
    delete this->velocity;
    this->velocity = nullptr;
}