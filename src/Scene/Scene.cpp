#include "Scene.hpp"
#include "../Player/Player.hpp"
#include "../Bullet/Bullet.hpp"

Scene::Scene() {
}

bool Scene::init(SDL_Renderer* renderer) {
    this->gRenderer = renderer;
    Player *player = new Player();
    player->init(this->gRenderer);
    this->instantiate(player);

    gMusic = Mix_LoadMUS( "assets/Music/music.mp3" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        return false;
    }

    if( Mix_PlayingMusic() == 0 )
    {
        Mix_PlayMusic( gMusic, -1 );
    }

    return true;
}

void Scene::instantiate(GameObject* gameObject) {
    if (gameObject == nullptr) {
        SDL_Log("ERROR: Trying to instantiate nullptr!");
        return;
    }
    
    gameObject->init(this->gRenderer);
    gameObject->setScene(this);
    this->gameObjects.push_back(gameObject);
}

void Scene::queueInstantiate(GameObject* gameObject) {
    if (gameObject == nullptr) {
        SDL_Log("ERROR: Trying to queue nullptr!");
        return;
    }
    
    pendingObjects.push_back(gameObject);
}

void Scene::processPendingObjects() {
    for(auto& obj : pendingObjects) {
        if (obj != nullptr) {
            obj->init(this->gRenderer);
            obj->setScene(this);
            gameObjects.push_back(obj);
        }
    }
    pendingObjects.clear();
}

void Scene::processInput(SDL_Event& e) {
    for(auto& gameObject : this->gameObjects) {
        gameObject->processInput(e);
    }
}

void Scene::update() {
    processPendingObjects();
    
    for(auto it = gameObjects.begin(); it != gameObjects.end(); ) {
        GameObject* gameObject = *it;
        
        if (gameObject == nullptr) {
            it = gameObjects.erase(it);
            continue;
        }
        
        if (Bullet* bullet = dynamic_cast<Bullet*>(gameObject)) {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - bullet->getSinceCreated() >= bullet->getLifetime()) {
                it = gameObjects.erase(it);
                delete bullet;
                continue;
            }
        }
        
        gameObject->update();
        ++it;
    }
}

void Scene::render(SDL_Renderer* renderer) {

    SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear( renderer );
    
    for(auto& gameObject : this->gameObjects) {
        gameObject->render();
    }

    SDL_RenderPresent( renderer );
}

Scene::~Scene() {
    Mix_FreeMusic( gMusic );
    gMusic = nullptr;

    for(auto& obj : pendingObjects) {
        if (obj != nullptr) {
            delete obj;
        }
    }
    pendingObjects.clear();
    
    for(auto& obj : gameObjects) {
        if (obj != nullptr) {
            delete obj;
        }
    }
    gameObjects.clear();
}