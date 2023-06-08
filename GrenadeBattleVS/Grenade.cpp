#include "Grenade.h"
#include "AssetManager.h"
#include "VectorHelper.h"

Grenade::Grenade()
	: PhysicsObject()
    , fuseTimer(8000)
    , explodeTimer(200)
{
    // Starting texture
    sprite.setTexture(AssetManager::RequestTexture("grenade"));

    // Set origin and scale
    sprite.setOrigin(AssetManager::RequestTexture("grenade").getSize().x / 2, AssetManager::RequestTexture("grenade").getSize().y / 2);
    sprite.setScale(3.0f, 3.0f);

    collisionOffset = sf::Vector2f(-36.0f, -36.0f);
    collisionScale = sf::Vector2f(0.2f, 0.25f);
}

void Grenade::Update(sf::Time frameTime)
{
    PhysicsObject::Update(frameTime);
    if (fuseTimer > 0)
        --fuseTimer;
    
    if (fuseTimer == 0)
    {
        if (explodeTimer > 0)
            --explodeTimer;
    }
}

void Grenade::HandleCollision(Object& otherObj)
{
    sf::Vector2f depth = GetCollisionDepth(otherObj);
    sf::Vector2f newPos = GetPosition();
    sf::Vector2f normal = VectorHelper::GetNormal(velocity);

    if (abs(depth.x) < abs(depth.y))
    {
        // Move in x direction
        newPos.x += depth.x * 1.1f;
        velocity.x = VectorHelper::GetReflection(velocity, normal).x;
        acceleration.x = -acceleration.x;
    }
    else
    {
        // Move in y direction
        newPos.y += depth.y * 1.1f;
        velocity.y = VectorHelper::GetReflection(velocity, normal).y;
        acceleration.y = -acceleration.y;
    }

    SetPosition(newPos);
}

void Grenade::SetVelocity(sf::Vector2f newVel)
{
    velocity = newVel;
}

int Grenade::GetFuseTimer()
{
    return fuseTimer;
}

int Grenade::GetExplodeTimer()
{
    return explodeTimer;
}

void Grenade::DecreaseFuseTimer()
{
    --fuseTimer;
}

void Grenade::DecreaseExplodeTimer()
{
    --explodeTimer;
}

void Grenade::Explode()
{
    sprite.setTexture(AssetManager::RequestTexture("explosion"));
    collisionScale = sf::Vector2f(0.9f, 0.9f);
}