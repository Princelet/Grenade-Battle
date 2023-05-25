#include "Grenade.h"
#include "AssetManager.h"

Grenade::Grenade()
	: PhysicsObject()
{
    // Starting texture
    sprite.setTexture(AssetManager::RequestTexture("grenade"));

    // Set origin and scale
    sprite.setOrigin(AssetManager::RequestTexture("grenade").getSize().x / 2, AssetManager::RequestTexture("grenade").getSize().y / 2);
    sprite.setScale(3.0f, 3.0f);

    collisionOffset = sf::Vector2f(-36.0f, -36.0f);
    collisionScale = sf::Vector2f(0.2f, 0.25f);
}

void Grenade::HandleCollision(Object& otherObj)
{
    sf::Vector2f depth = GetCollisionDepth(otherObj);
    sf::Vector2f newPos = GetPosition();

    if (abs(depth.x) < abs(depth.y))
    {
        // Move in x direction
        velocity.x = -velocity.x;
        acceleration.x = -acceleration.x;
    }
    else
    {
        // Move in y direction
        velocity.y = -velocity.y;
        acceleration.y = -acceleration.y;
    }

    SetPosition(newPos);
}