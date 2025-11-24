#include "Bullet.hpp"
#include "../Game/Game.hpp"

const float BULLET_SPEED = 20.f;

Bullet::Bullet(Player *owner) : owner{ owner } {
    this->position = new Vector2( this->owner->getPosition().getX()+15, this->owner->getPosition().getY()+15 );
    this->velocity = new Vector2( 0.f, 0.f );
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    Vector2 mousePos = Vector2(mouseX, mouseY);
    Vector2 direction = mousePos - this->owner->getPosition();
    float length = std::sqrt(direction.getX() * direction.getX() + direction.getY() * direction.getY());
    if (length != 0) {
        direction = direction / length;
        this->velocity->setX(direction.getX() * BULLET_SPEED);
        this->velocity->setY(direction.getY() * BULLET_SPEED);
    }

    this->sinceCreated = SDL_GetTicks();
    this->lifetime = 1000;
}

void Bullet::init(SDL_Renderer* renderer) {
    this->texture = new Texture( renderer );
    if( this->texture->loadFromFile("assets/img/dots.png") == false )
    {
        SDL_Log( "Failed to load Bullet texture");
    }
}


void Bullet::processInput(SDL_Event& e) {}

void Bullet::update() {
    this->position->setX( this->position->getX() + this->velocity->getX() );
    this->position->setY( this->position->getY() + this->velocity->getY() );

}

void Bullet::render() {
    SDL_FRect spriteClip{ 0.f, 100.f, 100.f, 100.f };
    this->texture->render( this->position->getX(), this->position->getY(), &spriteClip, 10.f, 10.f );
}

Bullet::~Bullet() {
    delete this->texture;
    this->texture = nullptr;
    delete this->position;
    this->position = nullptr;
    delete this->velocity;
    this->velocity = nullptr;
}