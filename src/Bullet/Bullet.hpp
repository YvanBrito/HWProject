#include "Texture/Texture.hpp"
#include "Vector2/Vector2.hpp"
#include "Player/Player.hpp"

class Bullet: public GameObject {
public:
    Bullet(Player *owner);

    void init(SDL_Renderer* renderer) override;
    void processInput(SDL_Event& e) override;
    void update() override;
    void render() override;
    Uint32 getSinceCreated() const { return sinceCreated; }
    Uint32 getLifetime() const { return lifetime; }

    ~Bullet();
private:
    Texture *texture;
    Vector2 *velocity;
    Vector2 *position;
    Player *owner;
    Uint32 sinceCreated;
    Uint32 lifetime;
};