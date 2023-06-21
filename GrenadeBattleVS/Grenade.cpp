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
    sprite.setScale(3.0f, 3.0f);
    sprite.setOrigin(AssetManager::RequestTexture("grenade").getSize().x / 2, AssetManager::RequestTexture("grenade").getSize().y / 2);

    collisionOffset = sf::Vector2f(-36.0f, -36.0f);
    collisionScale = sf::Vector2f(0.2f, 0.25f);
    hasDrag = false;
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

    sf::Vector2f normal;
    sf::Vector2f pointA;
    sf::Vector2f pointB;
    
    // Top left = otherObj.left, otherObj.top
    // Top right = otherObj.left + otherObj.width, otherObj.top
    // Bottom left = otherObj.left, otherObj.top + otherObj.height
    // Bottom right = otherObj.left + otherObj.width, otherObj.top + otherObj.height

    // pointA - pointB = the line for normal

    if (abs(depth.x) < abs(depth.y))
    {
        // Top left
        pointA = sf::Vector2f(otherObj.GetAABB().left, otherObj.GetAABB().top);
        // Bottom left
        pointB = sf::Vector2f(otherObj.GetAABB().left, otherObj.GetAABB().top + otherObj.GetAABB().height);

        // Move in x direction
        newPos.x += depth.x * 2.0f;
    }
    else
    {
        // Top left
        pointA = sf::Vector2f(otherObj.GetAABB().left, otherObj.GetAABB().top);
        // Top right
        pointB = sf::Vector2f(otherObj.GetAABB().left + otherObj.GetAABB().width, otherObj.GetAABB().top);

        // Move in y direction
        newPos.y += depth.y * 2.0f;
    }

    // Get normal
    normal = VectorHelper::Normalise(VectorHelper::GetNormal(sf::Vector2f(pointA - pointB)));
    // Set velocity to reflect
    velocity = VectorHelper::GetReflection(velocity, normal);

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