#include "Player.h"
#include "AssetManager.h"
#include "LevelScreen.h"
#include "Grenade.h"

Player::Player(LevelScreen* newLevel)
    : PhysicsObject()
    , p1(true)
    , level(newLevel)
    , canJump(true)
    , grenadeTimer(0)
{
    // Starting texture
    sprite.setTexture(AssetManager::RequestTexture("player_1_stand"));

    // Set origin and scale
    sprite.setOrigin(AssetManager::RequestTexture("player_1_stand").getSize().x / 2, AssetManager::RequestTexture("player_1_stand").getSize().y / 2);
    sprite.setScale(2.0f, 2.0f);

    // Practical Task - Collision Geometry
    collisionOffset = sf::Vector2f(-24.0f, -23.0f);
    collisionScale = sf::Vector2f(0.9f, 1.0f);

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
    const float JUMPSPEED = 400;

    float pipTime = 0;
    float pipTimeStep = 0.1f;

    for (size_t i = 0; i < pips.size(); ++i)
    {
        pips[i].setPosition(GetPipPosition(pipTime));
        pipTime += pipTimeStep;
    }

    if (p1)
    {
        if (sf::Joystick::isButtonPressed(0, 5))
        {
            Fire(sf::Vector2f(500.0f, 500.0f));
        }
        if (canJump)
        {
            if (sf::Joystick::isButtonPressed(0, 0))
            {
                velocity.y = -JUMPSPEED;
                canJump = false;
            }
        }
    }
    else
    {
        if (sf::Joystick::isButtonPressed(1, 5))
        {
            Fire(sf::Vector2f(500.0f, 500.0f));
        }
        if (canJump)
        {
            if (sf::Joystick::isButtonPressed(1, 0))
            {
                velocity.y = -JUMPSPEED;
                canJump = false;
            }
        }
    }

    for (size_t i = 0; i < grenades.size(); ++i)
    {
        if (grenades[i])
        {
            if (grenades[i]->GetFuseTimer() > 0)
                grenades[i]->DecreaseFuseTimer();

            if (grenades[i]->GetFuseTimer() == 0)
            {
                grenades[i]->Explode();

                if (grenades[i]->GetExplodeTimer() > 0)
                    grenades[i]->DecreaseExplodeTimer();

                if (grenades[i]->GetExplodeTimer() == 0)
                {
                    delete grenades[i];
                    grenades[i] = nullptr;
                }
            }
        }
    }

    UpdateAcceleration();

    if (grenadeTimer > 0)
        --grenadeTimer;
}

void Player::Draw(sf::RenderTarget& target)
{
    Object::Draw(target);

    // Draw the pips
    for (size_t i = 0; i < pips.size(); ++i)
    {
        target.draw(pips[i]);
    }
    for (size_t i = 0; i < grenades.size(); ++i)
    {
        if (grenades[i])
            grenades[i]->Draw(target);
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

void Player::SetCanJump(bool newCanJump)
{
    canJump = newCanJump;
}

void Player::Fire(sf::Vector2f firingVel)
{
    if (grenadeTimer == 0)
    {
        grenades.push_back(new Grenade);
        grenades[grenades.size() - 1]->SetVelocity(sf::Vector2f(500.0f, 500.0f));
        grenades[grenades.size() - 1]->SetPosition(GetPosition());
        
        grenadeTimer = 600;
    }
}

void Player::ClearGrenades()
{
    for (size_t i = 0; i < grenades.size(); ++i)
    {
        delete grenades[i];
        grenades[i] = nullptr;
    }

    grenades.clear();
}

std::vector<Grenade*> Player::GetGrenades()
{
    return grenades;
}

void Player::UpdateAcceleration()
{
    const float ACCEL = 3000;
    const float GRAVITY = 1000;
    const float DEADZONE = 25;

    // Update acceleration
    acceleration.x = 0;
    acceleration.y = GRAVITY;

    if (p1)
    {
        // P1 Movement
        sf::Vector2f direction(0, 0);
        if (sf::Joystick::isConnected(0))
        {
            if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -DEADZONE)
            {
                acceleration.x = -ACCEL;
                sprite.setScale(2.0f, 2.0f);
            }
            if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > DEADZONE)
            {
                acceleration.x = ACCEL;
                sprite.setScale(-2.0f, 2.0f);
            }
        }
    }
    else
    {
        // P2 Movement
        sf::Vector2f direction(0, 0);
        if (sf::Joystick::isConnected(1))
        {
            if (sf::Joystick::getAxisPosition(1, sf::Joystick::X) < -DEADZONE)
            {
                acceleration.x = -ACCEL;
                sprite.setScale(-2.0f, 2.0f);
            }
            if (sf::Joystick::getAxisPosition(1, sf::Joystick::X) > DEADZONE)
            {
                acceleration.x = ACCEL;
                sprite.setScale(2.0f, 2.0f);
            }
        }
    }
}

sf::Vector2f Player::GetPipPosition(float pipTime)
{
    // Practical Task - Gravity Prediction [UNFINISHED]

    return sf::Vector2f(0, 1000) * pipTime * pipTime
        + sf::Vector2f(500, -1000) * pipTime
        + sf::Vector2f(500, 500);
}