#include "Player.hpp"
#include "../Game/Game.hpp"
#include "../Bullet/Bullet.hpp"

const float PLAYER_SPEED = 5.f;
unsigned int lastPressedKeyHor = 0;
unsigned int lastPressedKeyVer = 0;
bool mouseLeftHeld = false;
int shootCooldown = 0;

Player::Player() {
    this->position = new Vector2( Game::kScreenWidth / 2.f, Game::kScreenHeight / 2.f );
    this->velocity = new Vector2( 0.f, 0.f );
}

void Player::init(SDL_Renderer* renderer) {
    this->texture = new Texture( renderer );
    if( this->texture->loadFromFile("assets/img/dots.png") == false )
    {
        SDL_Log( "Failed to load player texture");
    }

    this->gShot = Mix_LoadWAV( "assets/SFX/shot.mp3" );
    if( this->gShot == nullptr )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}

void Player::processInput(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        if( e.key.keysym.sym == SDLK_w )
        {
            this->velocity->setY( -PLAYER_SPEED );
            lastPressedKeyVer = SDLK_w;
        }
        if( e.key.keysym.sym == SDLK_s )
        {
            this->velocity->setY( PLAYER_SPEED );
            lastPressedKeyVer = SDLK_s;
        }
        if( e.key.keysym.sym == SDLK_a )
        {
            this->velocity->setX( -PLAYER_SPEED );
            lastPressedKeyHor = SDLK_a;
        }
        if( e.key.keysym.sym == SDLK_d )
        {
            this->velocity->setX( PLAYER_SPEED );
            lastPressedKeyHor = SDLK_d;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        if( e.key.keysym.sym == SDLK_w && lastPressedKeyVer == SDLK_w )
        {
            this->velocity->setY( 0.f );
        }
        if(e.key.keysym.sym == SDLK_s && lastPressedKeyVer == SDLK_s)
        {
            this->velocity->setY( 0.f );
        }
        if( e.key.keysym.sym == SDLK_a && lastPressedKeyHor == SDLK_a )
        {
            this->velocity->setX( 0.f );
        }
        if( e.key.keysym.sym == SDLK_d && lastPressedKeyHor == SDLK_d )
        {
            this->velocity->setX( 0.f );
        }
    }
    
    if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
    {
        mouseLeftHeld = true;
    }
    
    if(e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
    {
        mouseLeftHeld = false;
    }
}

void Player::update() {
    if (mouseLeftHeld) {
        if (shootCooldown <= 0) {
            Bullet* bullet = new Bullet(this);
            scene->queueInstantiate(bullet);
            Mix_PlayChannel( -1, this->gShot, 0 );
            shootCooldown = 10;
        }
        shootCooldown--;
    }

    this->position->setX( this->position->getX() + this->velocity->getX() );
    this->position->setY( this->position->getY() + this->velocity->getY() );
    if (this->position->getX() < 0.f)
        this->position->setX(0.f);
    if (this->position->getX() > Game::kScreenWidth - 30.f)
        this->position->setX(Game::kScreenWidth - 30.f);
    if (this->position->getY() < 0.f)
        this->position->setY(0.f);
    if (this->position->getY() > Game::kScreenHeight - 30.f)
        this->position->setY(Game::kScreenHeight - 30.f);
}

void Player::render() {
    SDL_FRect spriteClip{ 100.f, 0.f, 100.f, 100.f };
    this->texture->render( this->position->getX(), this->position->getY(), &spriteClip, 30.f, 30.f );
}

Vector2 Player::getPosition() {
    return *(this->position);
}

Player::~Player() {
    delete this->texture;
    this->texture = nullptr;
    delete this->position;
    this->position = nullptr;
    delete this->velocity;
    this->velocity = nullptr;

    Mix_FreeChunk( this->gShot );
    this->gShot = nullptr;
}