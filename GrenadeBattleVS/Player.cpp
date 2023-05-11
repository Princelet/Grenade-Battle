#include "Player.h"
#include "AssetManager.h"

Player::Player()
    : PhysicsObject()
    , p1(true)
{
    // Starting texture
    sprite.setTexture(AssetManager::RequestTexture("player_1_stand"));

    // Set origin and scale
    sprite.setOrigin(AssetManager::RequestTexture("player_1_stand").getSize().x / 2, AssetManager::RequestTexture("player_1_stand").getSize().y / 2);
    sprite.setScale(2.0f, 2.0f);

    collisionOffset = sf::Vector2f(-24.0f, -23.0f);
    collisionScale = sf::Vector2f(0.9f, 1.0f);

    oldPosition = sf::Vector2f(100, 100);
    acceleration = sf::Vector2f(100, 100);

    // Add sprite to my pips
    const int NUM_PIPS = 5;
    for (int i = 0; i < NUM_PIPS; ++i)
    {
        pips.push_back(sf::Sprite());
        pips[i].setTexture(AssetManager::RequestTexture("pip"));
        pips[i].scale(2.0f, 2.0f);
    }
}

void Player::Update(sf::Time frameTime)
{
    PhysicsObject::Update(frameTime);
    UpdateAcceleration();

    float pipTime = 0;
    float pipTimeStep = 0.1f;

    for (size_t i = 0; i < pips.size(); ++i)
    {
        pips[i].setPosition(GetPipPosition(pipTime));
        pipTime = pipTimeStep;
    }
}

void Player::Draw(sf::RenderTarget& target)
{
    Object::Draw(target);

    // Draw the pips
    for (size_t i = 0; i < pips.size(); ++i)
    {
        target.draw(pips[i]);
    }

    if (p1)
    {
        sprite.setTexture(AssetManager::RequestTexture("player_1_stand"));
    }
    else
    {
        sprite.setTexture(AssetManager::RequestTexture("player_2_stand"));
    }
}

void Player::SetP1(bool isP1)
{
    p1 = isP1;
}

void Player::UpdateAcceleration()
{
    const float ACCEL = 3000;
    const float GRAVITY = 1000;

    // Update acceleration
    acceleration.x = 0;
    acceleration.y = GRAVITY;

    // Temp 2p movement
    if (p1)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            acceleration.x = -ACCEL;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            acceleration.x = ACCEL;
        }
    }
    else
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            acceleration.x = -ACCEL;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            acceleration.x = ACCEL;
        }

    }

}

sf::Vector2f Player::GetPipPosition(float pipTime)
{
    return sf::Vector2f(0, 1000) * pipTime * pipTime
        + sf::Vector2f(500, -1000) * pipTime
        + sf::Vector2f(500, 500);
}
