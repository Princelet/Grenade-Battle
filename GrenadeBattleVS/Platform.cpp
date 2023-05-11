#include "Platform.h"
#include "AssetManager.h"

Platform::Platform(sf::Vector2f newPosition)
	: Object()
{
	sprite.setTexture(AssetManager::RequestTexture("tile"));
	sprite.setScale(2.0f, 2.0f);
	collisionOffset = sf::Vector2f(0.0f, 0.0f);
	collisionScale = sf::Vector2f(1.0f, 1.0f);
	SetPosition(newPosition);
}

Platform::~Platform()
{
}