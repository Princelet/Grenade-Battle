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