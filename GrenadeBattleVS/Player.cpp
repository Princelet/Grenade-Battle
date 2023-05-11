#include "Player.h"
#include "AssetManager.h"

Player::Player()
    : PhysicsObject()
{
    // Starting texture
    sprite.setTexture(AssetManager::RequestTexture("player_1_stand"));

    // Set origin and scale
    sprite.setOrigin(AssetManager::RequestTexture("player_1_stand").getSize().x / 2, AssetManager::RequestTexture("player_1_stand").getSize().y / 2);
    sprite.setScale(0.25f, 0.25f);

    collisionOffset = sf::Vector2f(-27.0f, -48.0f);
    collisionScale = sf::Vector2f(1.1f, 1.0f);

    oldPosition = sf::Vector2f(100, 300);
    acceleration = sf::Vector2f(100, 100);

    // Add sprite to my pips
    const int NUM_PIPS = 5;
    for (int i = 0; i < NUM_PIPS; ++i)
    {
        pips.push_back(sf::Sprite());
        pips[i].setTexture(AssetManager::RequestTexture("pip"));
    }
}

void Player::Update(sf::Time frameTime)
{
    PhysicsObject::Update(frameTime);

    float pipTime = 0;
    float pipTimeStep = 0.1f;

    for (int i = 0; i < pips.size(); ++i)
    {
        pips[i].setPosition(GetPipPosition(pipTime));
        pipTime = pipTimeStep;
    }
}

void Player::Draw(sf::RenderTarget& target)
{
    Object::Draw(target);

    // Draw the pips
    for (int i = 0; i < pips.size(); ++i)
    {
        target.draw(pips[i]);
    }
}

sf::Vector2f Player::GetPipPosition(float pipTime)
{
    return sf::Vector2f(0, 1000) * pipTime * pipTime
        + sf::Vector2f(500, -1000) * pipTime
        + sf::Vector2f(500, 500);
}
